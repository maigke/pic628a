#include "matrizLed.h"

unsigned int buscaDirEEPROM(char dat)
{
    unsigned int memoria;
    unsigned char caracter;
    
    unsigned char DatosAlmacenados = NUM_OF_CHARACTERS;
    for(unsigned char i = 0; i < DatosAlmacenados;i++)
    {
        //printCad("\nDirBuscada: "); enviaHexByte(10*i); 
         memoria = lee93LC66B(10*i);
         caracter = memoria & 0x00FF;
         //printCad("--- mem:");enviaHexByte(caracter); printCad("\n");
         if((dat - caracter) == 0)
             return (10*i);
    }
    return 5;
}

void printCad93LC66B(const char *cad)
{
    unsigned char i = 0;
    unsigned int memoria=0, dir;
    unsigned char numPatrones;
    uint8_t const S[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    uint8_t message[10]={0};
    int y,n,p;
    
    while(cad[i]!= 0)
    {
        //printCad("\n");
        //enviaRS232(cad[i]);
        //printCad("- char-: ");
        //enviaHexByte(cad[i]);
        dir = buscaDirEEPROM(cad[i]);
        //printCad("  -dir-:");
        //enviaHexByte(dir);
        //printCad("\n");
        if (dir != 5)
        {
            memoria = lee93LC66B(dir);
            numPatrones = (memoria >> 8) & (0x00FF);
            
            //printCad("NumPat: ");
            //enviaHexByte(numPatrones);
            //printCad("\n");
            
            for (int j = 0; j <= numPatrones; j++)
            {
                if((j+2)%2 == 0)
                {
                    memoria = lee93LC66B(dir+j+2);
                    message[j+1] = (memoria >> 8) & 0x00FF;
                    message[j] = memoria & 0x00FF;
                    //printCad("Direccion [");enviaHexByte(j);
                    //printCad("]: ");
                    //enviaHexByte((memoria >> 8) & 0x00FF);
                    //enviaHexByte(memoria & 0x00FF);
                    //printCad("\r\n");
                }
            }

            //for( y = 0; y < numPatrones+8; y++)
            //{
                for( p = 0; p < 32; p++)
                {
                    for(n=0;n<8;n++)
                    {
                        H595(~message[n],S[n]);
                        __delay_us(5);
                        H595(0,0);
                    }
                }
            //}
            //Debug de contenido de mensaje
            //printCad("Msg::---\n");
            //for(int i = 0; i < numPatrones+1; i++)
            //{
            //    enviaHexByte(i);
            //    printCad(":-");
            //    enviaHexByte(message[i]);
            //    printCad("--");
            //}
        }
    i++;    
    }
}
