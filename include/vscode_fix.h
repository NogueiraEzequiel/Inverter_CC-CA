#ifndef VSCODE_FIX_H
#define VSCODE_FIX_H

// Este bloque SOLO lo lee VS Code (IntelliSense).
#ifdef __INTELLISENSE__

    typedef unsigned char  uint8_t;
    typedef unsigned short uint16_t;
    typedef uint8_t  BYTE;
    typedef uint16_t WORD;

    // --- PUERTOS ---
    extern volatile BYTE LATA;
    extern volatile BYTE TRISA;
    extern volatile BYTE PORTA;
    extern volatile BYTE LATB;
    extern volatile BYTE TRISB;
    extern volatile BYTE PORTB;
    extern volatile BYTE LATC;
    extern volatile BYTE TRISC;
    extern volatile BYTE PORTC;

    // --- ESTRUCTURAS DE BITS ---
    typedef struct { unsigned ADON:1; unsigned GO_DONE:1; unsigned CHS:4; } ADCON0bits_t;
    extern volatile ADCON0bits_t ADCON0bits;
    extern volatile BYTE ADCON0;

    typedef struct { unsigned PCFG:4; unsigned VCFG0:1; unsigned VCFG1:1; } ADCON1bits_t;
    extern volatile ADCON1bits_t ADCON1bits;
    extern volatile BYTE ADCON1;

    typedef struct { unsigned ADCS:3; unsigned ACQT:3; unsigned ADFM:1; } ADCON2bits_t;
    extern volatile ADCON2bits_t ADCON2bits;
    extern volatile BYTE ADCON2;

    // --- AGREGADO: RESULTADO DEL ADC (ESTO SOLUCIONA TU ERROR) ---
    extern volatile BYTE ADRESH;
    extern volatile BYTE ADRESL;
    extern volatile uint16_t ADRES; // Por si usas el registro de 16 bits completo
    // -------------------------------------------------------------

    // TIMER 2
    typedef struct { unsigned T2CKPS:2; unsigned TMR2ON:1; unsigned TOUTPS:4; } T2CONbits_t;
    extern volatile T2CONbits_t T2CONbits;
    extern volatile BYTE T2CON;
    extern volatile BYTE PR2;

    // PWM
    extern volatile BYTE CCP1CON;
    extern volatile BYTE CCP2CON;
    extern volatile BYTE CCPR1L;
    extern volatile BYTE CCPR2L;

    // INTERRUPCIONES
    typedef struct { unsigned GIE:1; unsigned PEIE:1; unsigned TMR0IE:1; } INTCONbits_t;
    extern volatile INTCONbits_t INTCONbits;
    
    typedef struct { unsigned IPEN:1; } RCONbits_t;
    extern volatile RCONbits_t RCONbits;
    
    typedef struct { unsigned TMR1IF:1; unsigned TMR2IF:1; } PIR1bits_t;
    extern volatile PIR1bits_t PIR1bits;

    // BITS INDIVIDUALES
    typedef struct {
        unsigned LATB0:1; unsigned LATB1:1; unsigned LATB2:1; unsigned LATB3:1;
        unsigned LATB4:1; unsigned LATB5:1; unsigned LATB6:1; unsigned LATB7:1;
    } LATBbits_t;
    extern volatile LATBbits_t LATBbits;

    typedef struct {
        unsigned TRISC0:1; unsigned TRISC1:1; unsigned TRISC2:1; 
        unsigned TRISC3:1; unsigned TRISC4:1; unsigned TRISC5:1; unsigned TRISC6:1;
    } TRISCbits_t;
    extern volatile TRISCbits_t TRISCbits;
    
    typedef struct {
        unsigned TRISB0:1; unsigned TRISB1:1; unsigned TRISB2:1; unsigned TRISB3:1;
        unsigned TRISB4:1; unsigned TRISB5:1; unsigned TRISB6:1; unsigned TRISB7:1;
    } TRISBbits_t;
    extern volatile TRISBbits_t TRISBbits;

    typedef struct {
        unsigned RC0:1; unsigned RC1:1; unsigned RC2:1; 
        unsigned RC3:1; unsigned RC4:1; unsigned RC5:1; unsigned RC6:1;
    } PORTCbits_t;
    extern volatile PORTCbits_t PORTCbits;

    #ifndef __delay_ms
        #define __delay_ms(x) 
    #endif

#endif // __INTELLISENSE__
#endif // VSCODE_FIX_H