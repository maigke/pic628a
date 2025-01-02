/*
 * File:   h595.c
 * Author: mmont
 *
 * Created on 31 de diciembre de 2024, 01:18 PM
 */


#include "h595.h"


void H595 (int cat , int an)
{
    int y;
    shift(an,0);
    shift(cat,0);
    latch();
}


void shift(int val, int dir){
    int y;
    if (dir == 1){  // Desplazamiento hacia la derecha (MSB primero)
        for (y = 7; y >= 0; y--){
            DATA = (val >> y) & 0x01;  // Extrae el bit correspondiente desde el MSB
            clock();
        }
    }
    else {  // Desplazamiento hacia la izquierda (LSB primero)
        for (y = 0; y < 8; y++){
            DATA = (val >> (7 - y)) & 0x01;  // Extrae el bit correspondiente desde el LSB
            clock();
        }
    }
}


void clock(void){
    CLK  = 1;
    __delay_us(5);
    CLK = 0;
    __delay_us(5);
}

void latch(void){
    LATCH = 1;
    __delay_us(10);
    LATCH = 0;
}
