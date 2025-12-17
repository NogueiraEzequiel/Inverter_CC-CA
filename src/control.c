/**
 * @file control.c
 * @author Tomas Canistra & Nogueira Ezequiel 
 * @brief Implementación del Lazo de Control y Máquina de Estados.
 */

#include "../include/config.h"
#include "../include/control.h"
#include "../include/hardware.h"

// Variable global de estado
SystemState_t current_state = STATE_STANDBY;

// Estructura PID
PID_Context_t pid;

// Contador para ralentizar tareas (no ejecutar PID en cada ciclo de CPU)
unsigned int task_counter = 0;

/**
 * @brief Función auxiliar para leer el ADC.
 * @param channel Canal a leer (0=V_out, 1=I_out, etc.)
 * @return Valor de 10 bits (0-1023)
 */
unsigned int ADC_Read(unsigned char channel) {
    // 1. Seleccionar canal (Bits CHS3:CHS0 en ADCON0)
    // Limpiamos los bits de canal y ponemos el nuevo
    ADCON0 &= 0b11000011; 
    ADCON0 |= (channel << 2); 

    // 2. Tiempo de adquisición (El capacitor debe cargarse)
    __delay_ms(1); // Pequeño retardo para estabilizar

    // 3. Iniciar conversión (GO/DONE = 1)
    ADCON0bits.GO_DONE = 1;

    // 4. Esperar a que termine (GO/DONE = 0)
    while(ADCON0bits.GO_DONE);

    // 5. Devolver resultado (ADRESH:ADRESL)
    // Como está justificado a la derecha:
    return ((ADRESH << 8) + ADRESL);
}

void Control_Init(void) {
    current_state = STATE_STANDBY;
    
    // Inicializar PID
    // Suponemos que 220V en la salida equivalen a una lectura de 512 en el ADC
    // (Esto se debe calibrar con el divisor resistivo real del hardware)
    pid.target_adc = 512; 
    pid.integral_sum = 0;
    pid.last_error = 0;
    
    // Arrancar con amplitud 0 (Apagado)
    pwm_amplitude = 0;
}

void PID_Update(void) {
    // 1. Leer Feedback (Voltaje de salida - Canal 0)
    int feedback = ADC_Read(0);
    
    // 2. Calcular Error
    int error = pid.target_adc - feedback;
    
    // 3. Término Proporcional
    long p_term = PID_KP * error;
    
    // 4. Término Integral (con limitación para evitar Windup)
    pid.integral_sum += error;
    // Limitar la suma integral
    if (pid.integral_sum > 2000) pid.integral_sum = 2000;
    if (pid.integral_sum < -2000) pid.integral_sum = -2000;
    
    long i_term = PID_KI * pid.integral_sum;
    
    // 5. Término Derivativo
    long d_term = PID_KD * (error - pid.last_error);
    pid.last_error = error;
    
    // 6. Calcular Salida Total
    // Dividimos por un factor de escala si las ganancias son muy altas
    long output = pwm_amplitude + (p_term + i_term + d_term) / 10;
    
    // 7. Limitar salida (Saturación)
    if (output > PID_MAX) output = PID_MAX;
    if (output < PID_MIN) output = PID_MIN;
    
    // 8. Aplicar a la variable global que usa la ISR
    pwm_amplitude = (unsigned int)output;
}

void Control_Task(void) {
    // Ejecutar esta lógica cada cierto tiempo (ej. cada 100 ciclos de main)
    task_counter++;
    if (task_counter < 100) return;
    task_counter = 0;

    switch (current_state) {
        case STATE_STANDBY:
            // Chequear voltaje de batería (Canal 2 supongamos)
            // Si V_bat > 11V, iniciar
            if (ADC_Read(2) > 400) { // Valor de ejemplo
                current_state = STATE_SOFT_START;
                pwm_amplitude = 10; // Empezar bajito
            }
            break;

        case STATE_SOFT_START:
            // Subir el voltaje gradualmente (Rampa)
            if (pwm_amplitude < 800) {
                pwm_amplitude += 5; // Subir de a poco
            } else {
                // Llegamos a un voltaje decente, activar PID
                current_state = STATE_RUNNING;
            }
            break;

        case STATE_RUNNING:
            // El PID se encarga de mantener los 220V estables
            PID_Update();
            
            // Aquí verificar protecciones
            // Ej: Si Temp > 80C (Canal 4), ir a ERROR
            // if (ADC_Read(4) > 900) current_state = STATE_ERROR_TEMP;
            break;

        case STATE_ERROR_TEMP:
            // Apagar salida PWM
            pwm_amplitude = 0;
            // Pitar Buzzer
            Buzzer_Beep(100); 
            // Esperar que baje temp para reiniciar (Lógica simple)
            __delay_ms(1000);
            current_state = STATE_STANDBY;
            break;
            
        default:
            pwm_amplitude = 0;
            current_state = STATE_STANDBY;
            break;
    }
}