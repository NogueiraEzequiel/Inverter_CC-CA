/**
 * @file hardware.h
 * @author Tomas Canistra & Nogueira Ezequiel 
 * @brief Mapeo de pines y definiciones de hardware.
 * * Contiene las definiciones de macros para interactuar con los pines del
 * Inversor V4.0 (Buzzer, Fan, Entradas ADC, PWM).
 * También define la frecuencia del cristal para las rutinas de delay.
 */

#ifndef HARDWARE_H
#define HARDWARE_H

#include <xc.h>

// --- AGREGADO: Parche para que VS Code reconozca los registros ---
#include "vscode_fix.h"
// -----------------------------------------------------------------

/** * @brief Frecuencia del Oscilador
 * Definida en 20 MHz (Cristal HS).
 * Necesaria para que __delay_ms() calcule bien los tiempos.
 */
#define _XTAL_FREQ 20000000

/* --- SALIDAS DIGITALES (Actuadores) --- */

/** @brief Pin de control del Buzzer (Activo Alto) */
#define PIN_BUZZER      LATBbits.LATB5
#define TRIS_BUZZER     TRISBbits.TRISB5

/** @brief Pin de control del Cooler/Fan (Activo Alto) */
#define PIN_FAN         LATBbits.LATB4
#define TRIS_FAN        TRISBbits.TRISB4

/** @brief Pin de Sincronismo/Debug (Para Osciloscopio) */
#define PIN_SYNC        LATBbits.LATB7
#define TRIS_SYNC       TRISBbits.TRISB7

/* --- SALIDAS PWM (Puente H) --- */

/** @brief Salida PWM Rama A (CCP1 - RC2) */
#define TRIS_PWM1       TRISCbits.TRISC2

/** @brief Salida PWM Rama B (CCP2 - RC1) */
#define TRIS_PWM2       TRISCbits.TRISC1

/* --- ENTRADAS DIGITALES (Protecciones HW) --- */

/** @brief Entrada de protección de hardware (RC6) */
#define PIN_PROTECT     PORTCbits.RC6
#define TRIS_PROTECT    TRISCbits.TRISC6

/* --- PROTOTIPOS DE FUNCIONES DE HARDWARE --- */

/**
 * @brief Inicializa todos los periféricos del microcontrolador.
 * * Configura:
 * - Puertos I/O (TRIS/LAT)
 * - Convertidor ADC (Canales y tiempos)
 * - Timer 2 (Base de tiempo del PWM)
 * - Módulos CCP en modo PWM
 * - Interrupciones globales
 */
void System_Init(void);

/**
 * @brief Enciende el Buzzer por un tiempo determinado.
 * @param ms Duración en milisegundos.
 */
void Buzzer_Beep(unsigned int ms);

#endif /* HARDWARE_H */