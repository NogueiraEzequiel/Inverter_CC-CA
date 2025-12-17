/**
 * @file hardware.c
 * @author Tomas Canistra & Nogueira Ezequiel 
 * @brief Implementación de las funciones de inicialización de Hardware.
 */

// CORRECCIÓN: Usamos "../include/" para salir de "src" y entrar a "include"
#include "../include/config.h"
#include "../include/hardware.h"
#include "../include/tables.h" 

void System_Init(void) {
    // ---------------------------------------------------------
    // 1. Configuración de Puertos (TRIS y LAT)
    // ---------------------------------------------------------
    
    // PORTA: Entradas Analógicas (RA0..RA3, RA5)
    LATA = 0x00;
    TRISA = 0b00111111; // 1=Entrada, 0=Salida

    // PORTB: Salidas de control y Entradas digitales
    LATB = 0x00;        // Limpiar salidas
    TRISB = 0b00001111; // RB4-RB7 Salidas, RB0-RB3 Entradas

    // PORTC: Salidas PWM y Protecciones
    LATC = 0x00;
    TRISC = 0b11111001; // RC1 y RC2 Salidas, Resto Entradas

    // ---------------------------------------------------------
    // 2. Configuración del ADC (Convertidor Analógico-Digital)
    // ---------------------------------------------------------
    
    // ADCON1: Configuración de pines y voltaje de referencia.
    // Usamos asignación directa al registro para evitar errores de bits en VS Code.
    // Config: Vref=Vdd/Vss, AN0-AN4 Analógicos (PCFG=1010)
    ADCON1 = 0b00001010; 

    // ADCON2: Tiempo de adquisición y reloj
    // Config: Justificación Derecha (Bit 7=1), 4 TAD (Bit 5-3=010), Fosc/32 (Bit 2-0=010)
    ADCON2 = 0b10010010; 
    
    // ADCON0: Encender módulo ADC
    // Aquí podemos usar bits porque definimos ADCON0bits en el fix, 
    // pero por seguridad usamos el registro o el bit explícito.
    ADCON0bits.ADON = 1; 

    // ---------------------------------------------------------
    // 3. Configuración del PWM (Timer 2 + CCP)
    // ---------------------------------------------------------
    
    /* Frecuencia PWM ~19.53 kHz con Fosc=20MHz */
    PR2 = 249; // Registro de Periodo

    // Configuración CCP1 y CCP2 en modo PWM
    CCP1CON = 0b00001100; 
    CCP2CON = 0b00001100; 

    // Inicializar Duty Cycle en 0
    CCPR1L = 0;
    CCPR2L = 0;

    // Configuración del Timer 2
    // Asignamos el registro entero para evitar error en T2CONbits
    // Postscaler 1:1, Timer2 ON, Prescaler 1:1
    T2CON = 0b00000100; 

    // ---------------------------------------------------------
    // 4. Configuración de Interrupciones
    // ---------------------------------------------------------
    
    RCONbits.IPEN = 0;   // Deshabilitar prioridades
    INTCONbits.GIE = 1;  // Habilitar Interrupciones Globales
    INTCONbits.PEIE = 1; // Habilitar Interrupciones de Periféricos
}

void Buzzer_Beep(unsigned int ms) {
    PIN_BUZZER = 1;
    // __delay_ms espera una constante, usamos bucle para variable
    for(unsigned int i=0; i<ms; i++) {
        __delay_ms(1);
    }
    PIN_BUZZER = 0;
}