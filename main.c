/*
 * File:   main.c
 * Author: mmont
 *
 * Created on 31 de diciembre de 2024, 01:13 PM
 */
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 4000000

#include "h595.h"
#include "m93lc66b.h"
#include "rs232.h"
#include "matrizLed.h"

void main(void) {
    
    PCONbits.OSCF = 1; // ¡IMPORTANTE! Establecer OSCF para 4MHz
    
    TRISB = 0x00;
    init_93lc66b();
    init_rs232();
    
    LED = 1;
    //Condiciones de inicio
    CS = 0;
    DI = 0;
    SK = 0;
    //printCad("Iniciando test de comunicacion\r\n");
    
    while(1){
        printCad93LC66B("MONTY");
        __delay_ms(500);
        printCad93LC66B("2025");
        __delay_ms(500);
        
    }
    
    
    return;
}
