/**
 * @file tables.h
 * @author Tomas Canistra & Nogueira Ezequiel 
 * @brief Tablas de búsqueda (Look-up Tables) para generación de señal SPWM.
 * @date 2023-10-XX
 * * Este archivo contiene la tabla de valores precalculados de la función seno.
 * Almacenada como 'const' para que resida en la memoria de programa (Flash)
 * y no ocupe RAM.
 */

#ifndef TABLES_H
#define TABLES_H

#include <xc.h>

/**
 * @brief Cantidad de muestras por cada medio ciclo de la onda senoidal.
 * Ajustado para 50Hz con una frecuencia de PWM de ~20kHz.
 */
#define SINE_SAMPLES 98

/**
 * @brief Tabla de valores de la onda senoidal (0 a 180 grados).
 * * Escala: 0 a 1023 (10 bits) para coincidir con el PWM del PIC.
 * * Formato: SPWM Unipolar.
 */
const unsigned int SINE_TABLE[SINE_SAMPLES] = {
    0, 25, 50, 75, 100, 125, 150, 175, 199, 223, 
    247, 271, 294, 317, 340, 362, 384, 405, 426, 447,
    467, 487, 506, 525, 543, 560, 577, 593, 609, 624,
    638, 652, 665, 677, 689, 700, 710, 720, 729, 737,
    744, 751, 757, 762, 766, 770, 773, 775, 776, 776, // Pico (~90 grados)
    
    // Bajada simétrica
    775, 773, 770, 766, 762, 757, 751, 744, 737, 729,
    720, 710, 700, 689, 677, 665, 652, 638, 624, 609,
    593, 577, 560, 543, 525, 506, 487, 467, 447, 426,
    405, 384, 362, 340, 317, 294, 271, 247, 223, 199,
    175, 150, 125, 100, 75, 50, 25, 0
};

#endif /* TABLES_H */