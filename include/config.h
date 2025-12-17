/**
 * @file config.h
 * @author Tomas Canistra & Nogueira Ezequiel 
 * @brief Configuración de los Bits (Fuses) del PIC18F2520.
 * @date 2023-10-XX
 * * Este archivo define la configuración de hardware fundamental del microcontrolador.
 * Se establecen osciladores, protecciones de código y pines de función especial
 * según los requerimientos del Inversor V4.0.
 */

#ifndef CONFIG_H
#define CONFIG_H

// Inclusión de cabecera genérica del compilador XC8
#include <xc.h>

// --- SOLUCIÓN PARA VS CODE ---
// Forzamos la inclusión del archivo de definiciones del PIC18F2520.
// Esto hace que IntelliSense reconozca LATA, TRISA, ADCON1, etc.
// sin esperar a que el compilador lo haga por línea de comandos.
// -----------------------------

/* SECCIÓN 1: OSCILADOR */
/** * @brief Oscilador HS (High Speed)
 * Se utiliza un cristal externo de cuarzo.
 */
#pragma config OSC = HS

/* SECCIÓN 2: PROTECCIONES Y MONITOREO */
/** * @brief Fail-Safe Clock Monitor
 * Desactivado (OFF) porque usamos un cristal robusto.
 */
#pragma config FCMEN = OFF 

/** * @brief Internal/External Switchover
 * Desactivado (OFF). No necesitamos conmutar relojes.
 */
#pragma config IESO = OFF

/** * @brief Power-Up Timer (PWRT)
 * Activado (ON). Espera 64ms al encender para estabilizar la fuente antes de ejecutar código.
 */
#pragma config PWRT = ON

/** * @brief Brown-out Reset (BOR)
 * Desactivado (OFF). Ahorra consumo y evita reinicios intempestivos si Vdd fluctúa levemente.
 */
#pragma config BOREN = OFF 

/** * @brief Watchdog Timer (WDT)
 * Desactivado (OFF). Evita que el micro se resetee si el bucle principal tarda mucho.
 * @warning Si se activa, se debe limpiar el WDT en el main loop.
 */
#pragma config WDT = OFF

/* SECCIÓN 3: PINES Y PERIFÉRICOS */
/** * @brief CCP2 MUX
 * Asigna la salida del módulo CCP2 al pin RC1 (PORTC).
 * Vital para tener las dos salidas PWM en el mismo puerto.
 */
#pragma config CCP2MX = PORTC

/** * @brief PORTB A/D Enable
 * Desactivado (OFF). Configura pines PORTB<4:0> como E/S digitales al reset.
 */
#pragma config PBADEN = OFF

/** * @brief Low Voltage Programming (LVP)
 * Desactivado (OFF). Permite usar el pin RB5 como I/O digital normal 
 * (usado para el Buzzer en este proyecto).
 */
#pragma config LVP = OFF

/** * @brief Stack Overflow Reset
 * Activado (ON). Resetea el micro si se desborda la pila de llamadas.
 */
#pragma config STVREN = ON

/** * @brief Extended Instruction Set (XINST)
 * Desactivado (OFF). Usamos el set de instrucciones estándar (Legacy).
 */
#pragma config XINST = OFF

/** * @brief Debugging
 * Desactivado (OFF). Libera los pines RB6 y RB7 para uso general.
 */
#pragma config DEBUG = OFF

#endif /* CONFIG_H */