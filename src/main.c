/**
 * @file main.c
 * @author Tomas Canistra & Nogueira Ezequiel 
 * @brief Programa principal del Inversor CC-CA.
 * @version 4.0 Rev02
 */

// CORRECCIÓN: Rutas relativas para salir de "src" e ir a "include"
#include "../include/config.h"
#include "../include/hardware.h"
#include "../include/control.h"
#include "../include/tables.h"

void main(void) {
    // 1. Inicialización del Hardware (Pines, ADC, PWM, Timer2)
    System_Init();
    
    // 2. Inicialización de Variables de Control (PID, Estados)
    // Descomentado porque ya implementamos control.c
    Control_Init(); 

    // Test de Arranque: Pitido corto para indicar "Vivo"
    Buzzer_Beep(200);

    // 3. Bucle Principal (Super Loop)
    while (1) {
        // Ejecutar la máquina de estados y el PID
        Control_Task();
        
        // Pequeño retardo para liberar CPU (opcional, ajusta según necesidad)
        // __delay_ms(1); 
    }
}