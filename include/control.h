/**
 * @file control.h
 * @author Tomas Canistra & Nogueira Ezequiel 
 * @brief Definiciones para el lazo de control PID y Máquina de Estados.
 * * Define los estados operativos del inversor (Standby, Run, Error) y
 * las estructuras de datos para el controlador de voltaje.
 */

#ifndef CONTROL_H
#define CONTROL_H

#include <xc.h>
#include "vscode_fix.h" // Necesario para evitar errores en tipos de datos

// --- VARIABLE COMPARTIDA CON ISR (Interrupción) ---
/**
 * @brief Amplitud de la senoidal (0 a 1023).
 * Esta variable se define en isr.c pero se modifica en control.c.
 * El 'extern' le dice al compilador que la busque en otro lado.
 */
extern volatile unsigned int pwm_amplitude;

// --- DEFINICIONES DE ESTADO ---
/**
 * @brief Estados de la Máquina de Estados Finita (FSM).
 */
typedef enum {
    STATE_STANDBY,      /**< Esperando condiciones de batería (Salida OFF). */
    STATE_SOFT_START,   /**< Subiendo voltaje progresivamente (Rampa). */
    STATE_RUNNING,      /**< Funcionamiento normal (PID Activo). */
    STATE_ERROR_BAT,    /**< Error: Batería baja (<10.5V) o alta (>15V). */
    STATE_ERROR_TEMP,   /**< Error: Temperatura crítica. */
    STATE_ERROR_SHORT   /**< Error: Cortocircuito detectado. */
} SystemState_t;

// --- CONFIGURACIÓN DEL PID ---
// Ajustar estos valores según pruebas reales (Ziegler-Nichols o tanteo)
#define PID_KP  10      // Ganancia Proporcional
#define PID_KI  2       // Ganancia Integral
#define PID_KD  1       // Ganancia Derivativa
#define PID_MAX 1000    // Límite máximo del PWM
#define PID_MIN 0       // Límite mínimo

/**
 * @brief Estructura del Controlador PID.
 */
typedef struct {
    int target_adc;     // Valor ADC deseado (SetPoint) -> Ej: 512 para 220V
    long integral_sum;  // Acumulador del error integral
    int last_error;     // Error anterior (para derivativo)
} PID_Context_t;

// --- PROTOTIPOS ---

/**
 * @brief Inicializa las variables de control y estado.
 */
void Control_Init(void);

/**
 * @brief Tarea principal de control.
 * Debe llamarse periódicamente en el while(1) del main.
 * Maneja la máquina de estados y llama al PID.
 */
void Control_Task(void);

#endif /* CONTROL_H */