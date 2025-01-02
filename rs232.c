#include "rs232.h"

void init_rs232(void)
{
    //Configuracion para el puerto serial
    SPBRG = 0x19; //9600 bps
    TXSTA = 0x24; //transmision async habilitada
    RCSTA = 0x90; //Recepcion async hailitada
    TRISBbits.TRISB1 = 1;  //RX
    TRISBbits.TRISB2 = 0;  //TX
}


void enviaRS232(unsigned char dat)
{
    while(!TXSTAbits.TRMT);  //Espera a que el buffer este vacio
    TXREG = dat;   
}

void printCad(const char *cad)
{
    unsigned char i = 0;
    while(cad[i]!= 0){
        enviaRS232(cad[i]);
        i++;
    }
}

void enviaHexByte(unsigned char byte) {
    unsigned char nibble;

    nibble = (byte >> 4) & 0x0F;
    if (nibble < 10) {
        enviaRS232('0' + nibble);
    } else {
        enviaRS232('A' + nibble - 10);
    }

    nibble = byte & 0x0F;
    if (nibble < 10) {
        enviaRS232('0' + nibble);
    } else {
        enviaRS232('A' + nibble - 10);
    }
}
