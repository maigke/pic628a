#include "m93lc66b.h"

void init_93lc66b(void)
{
    TRISAbits.TRISA0 =0;
    TRISAbits.TRISA1 =0;
    TRISAbits.TRISA2 =0;
    TRISAbits.TRISA3 =1;
    CMCON = 0x07; // Habilita los pines para funciones I/O de PORTA
}

unsigned int shiftIn16(){
    int i;
    int temp = 0;
    int pinState;
    unsigned int myDataIn = 0;
    
    for (i = 15; i>=0; i--)
    {
        SK = 0;
        __delay_us(1);
        temp = DO;
        if(temp){
            pinState = 1;
            myDataIn = myDataIn | (1 << i);
        }else{
            pinState = 0;
        }
        SK = 1;
    }
    return myDataIn;
}

void startBit(void){
    CS = 0;
    __delay_us(1);
    SK = 0;
    DI = 0;
    CS = 1;
    __delay_us(1);
    DI = 1;
    __delay_us(1);
    SK = 1;   //flanco de subida 
    __delay_us(1);
    SK = 0;
    __delay_us(1);
}

unsigned int leeMemoria(){
    
    unsigned int Buffer = 0;
    SK = 0;
    Buffer = shiftIn16();
    //Buffer = (Buffer >> 8) | (Buffer << 8);
    return Buffer;
}

unsigned char bitRead(unsigned int data, unsigned char numeroBit)
{
    if((data)>>(numeroBit) & 0x01){
        return 1;
    }
        return 0;
}

void escribe(unsigned int dato, unsigned char contador)
{
    while(contador > 0)
    {
        __delay_us(1);  
        //Posicionamos el bit a leer de dato y lo copiamos a DI
        DI = bitRead(dato,(contador - 1));
        __delay_us(1);
        SK = 1;
        __delay_us(1);
        SK = 0;
        __delay_us(1);
        contador--;
    }
    DI = 0;
}

void leeAutomatico(unsigned int inicio, int alcance)
{
    unsigned int direccion = inicio;
    startBit();
    escribe(OPcode_Lectura,2);
    escribe(direccion, 9);
    if (alcance > direccion)
    {
        while(direccion <= alcance)
        {
            Buf = leeMemoria();
            __delay_ms(10);
            SK = 0;
            __delay_us(1);
            DI = 0;
            direccion++;
        }
    }else{
        Buf = leeMemoria();
        __delay_ms(10);
        SK = 0;
        __delay_us(1);
        DI = 0;
        
    }
}

unsigned int lee93LC66B(unsigned int direccion)
{
    unsigned int data=0;
    startBit();
    escribe(OPcode_Lectura,2);
    escribe(direccion, 9);
    data = leeMemoria();
    __delay_ms(10);
    SK = 0;
    __delay_us(1);
    DI = 0;
    return data;
}
