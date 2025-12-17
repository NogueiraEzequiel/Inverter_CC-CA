/**
 * @file isr.c
 * @author Tomas Canistra & Nogueira Ezequiel 
 * @brief Rutinas de Servicio de Interrupción (ISR).
 */

#include "../include/hardware.h"
#include "../include/tables.h"
#include <xc.h>

// --- TRUCO DEFINITIVO PARA VS CODE ---
// Si es VS Code (IntelliSense) el que lee esto, borramos "__interrupt()"
// Si es el compilador real, dejamos que funcione normal.
#ifdef __INTELLISENSE__
    #define __interrupt() 
#endif
// -------------------------------------

// Variables Volátiles
volatile unsigned char sine_index = 0;
volatile unsigned char semi_cycle_count = 0;
volatile unsigned int pwm_amplitude = 800; 

// Función de Interrupción
void __interrupt() ISR_High(void) {
    
    // Declaramos variables al principio para evitar líos de alcance
    unsigned long base_sample;
    unsigned long scaled_duty;
    unsigned char duty_H;
    unsigned char duty_L;

    // Verificamos flag de Timer 2
    if (PIR1bits.TMR2IF) {
        
        // 1. Limpiar Flag
        PIR1bits.TMR2IF = 0;
        
        // Debug
        PIN_SYNC = 1;

        // 2. Leer Tabla
        base_sample = SINE_TABLE[sine_index];
        
        // 3. Calcular Duty Cycle (Matemática)
        // (Base * Amplitud) / 1024
        scaled_duty = (base_sample * pwm_amplitude) >> 10;
        
        // Saturación (Protección)
        if (scaled_duty > 1023) {
            scaled_duty = 1023;
        }

        // 4. Separar bits (10 bits -> 8 altos + 2 bajos)
        duty_H = (unsigned char)(scaled_duty >> 2);
        duty_L = (unsigned char)(scaled_duty & 0x03);
        
        // Acomodar los bits bajos para el registro (bits 4 y 5)
        duty_L = (duty_L << 4);

        // 5. Aplicar al Hardware
        if (semi_cycle_count == 0) {
            // --- CICLO POSITIVO (Rama A) ---
            CCPR1L = duty_H;
            
            // Mascara para CCP1CON: Borramos bits 5-4 (0xCF) y ponemos los nuevos
            CCP1CON = (CCP1CON & 0xCF) | duty_L;
            
            // Apagar la otra rama
            CCPR2L = 0;
            CCP2CON = (CCP2CON & 0xCF);
        } 
        else {
            // --- CICLO NEGATIVO (Rama B) ---
            CCPR2L = duty_H;
            
            // Mascara para CCP2CON
            CCP2CON = (CCP2CON & 0xCF) | duty_L;
            
            // Apagar la otra rama
            CCPR1L = 0;
            CCP1CON = (CCP1CON & 0xCF);
        }

        // 6. Avanzar índice
        sine_index++;
        
        // Fin de tabla
        if (sine_index >= SINE_SAMPLES) {
            sine_index = 0;
            semi_cycle_count++;
            
            if (semi_cycle_count >= 2) {
                semi_cycle_count = 0;
            }
        }
        
        // Debug Off
        PIN_SYNC = 0;
    }
}