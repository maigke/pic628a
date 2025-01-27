/* 
 * File:   h595
 * Author: Miguel Montiel
 * Comments: Biblioteca para enviar datos a un 74595
 * Revision history: 0.1
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef H595_H
#define	H595_H

#include <xc.h> // include processor files - each processor file is guarded.  



// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star


#define _XTAL_FREQ 4000000

#define CLK PORTBbits.RB7
#define LATCH PORTBbits.RB6
#define DATA PORTBbits.RB5
#define LED PORTBbits.RB3

/**
 * @brief Controla dos registros de desplazamiento 74HC595 conectados en cascada.
 *
 * @param cat Valor a enviar al primer registro 74HC595 (generalmente para los c�todos de un display).
 * @param an Valor a enviar al segundo registro 74HC595 (generalmente para los �nodos de un display).
 *
 * @pre Los pines DATA, CLOCK y LATCH deben estar configurados como salidas. Las funciones shift() y latch() deben estar definidas.
 *
 * @details Esta funci�n env�a dos valores a trav�s de la funci�n shift() a dos registros 74HC595 conectados en cascada. Primero se env�a el valor 'an' y luego el valor 'cat'. Finalmente, se llama a la funci�n latch() para transferir los datos a las salidas de los registros.
 *
 * @code
 * // Ejemplo de uso: enviar 0xFF al registro de c�todos y 0x01 al registro de �nodos.
 * H595(0xFF, 0x01);
 * @endcode
 *
 * @remark El orden en que se env�an los datos (primero 'an' y luego 'cat') depende de la conexi�n f�sica de los registros en cascada. Aseg�rate de que este orden corresponda con tu hardware.
 */
void H595 (int cat , int an);

/**
 * @brief Realiza el desplazamiento de un valor bit a bit a trav�s del pin DATA.
 *
 * @param val Valor entero de 8 bits a desplazar.
 * @param dir Direcci�n del desplazamiento:
 *            - 1: Desplazamiento a la derecha (MSB primero).
 *            - 0: Desplazamiento a la izquierda (LSB primero).
 *
 * @pre El pin DATA debe estar configurado como salida. La funci�n clock() debe estar definida y generar un pulso de reloj.
 *
 * @return Ninguno.
 *
 * @details Esta funci�n implementa un desplazamiento bit a bit de un valor entero de 8 bits a trav�s del pin DATA. 
 *          Dependiendo del par�metro 'dir', el desplazamiento se realiza hacia la derecha (MSB primero) o hacia la izquierda (LSB primero).
 *          Despu�s de cada bit enviado, se llama a la funci�n clock() para generar un pulso de reloj.
 *
 * @code
 * // Ejemplo de uso: desplazar el valor 0b10101010 hacia la derecha
 * shift(0b10101010, 1);
 *
 * // Ejemplo de uso: desplazar el valor 0b01010101 hacia la izquierda
 * shift(0b01010101, 0);
 * @endcode
 *
 * @remark Es crucial que la funci�n clock() genere un pulso de reloj con la duraci�n correcta para el dispositivo receptor.
 */
void shift(int val,int dir);
/**
 * @brief Genera un pulso de reloj en el pin CLK.
 *
 * @pre El pin CLK debe estar configurado como salida.
 *
 * @details Esta funci�n genera un pulso de reloj de onda cuadrada en el pin CLK. El pulso consiste en un flanco ascendente (CLK = 1) seguido de un retardo de 5 microsegundos, y luego un flanco descendente (CLK = 0) seguido de otro retardo de 5 microsegundos. Esto resulta en un ciclo completo de 10 microsegundos.
 *
 * @code
 * clock(); // Genera un pulso de reloj de 10 microsegundos.
 * @endcode
 *
 * @note La precisi�n del retardo depende de la frecuencia del oscilador del microcontrolador. Aseg�rate de que la macro __delay_us() est� configurada correctamente para tu configuraci�n de hardware.
 *
 * @remark Es importante que la duraci�n del pulso de reloj sea compatible con las especificaciones del dispositivo al que se est� enviando la se�al de reloj (por ejemplo, el 74HC595).
 */
void clock(void);
/**
 * @brief Genera un pulso en el pin LATCH para transferir los datos a las salidas del registro 74HC595.
 *
 * @pre El pin LATCH debe estar configurado como salida.
 *
 * @details Esta funci�n genera un pulso positivo (de bajo a alto y luego a bajo) en el pin LATCH. Este pulso transfiere los datos que se han desplazado previamente a trav�s de la funci�n `shift()` a las salidas del registro 74HC595. El pulso en alto tiene una duraci�n de aproximadamente 10 microsegundos.
 *
 * @code
 * latch(); // Transfiere los datos a las salidas del registro 74HC595.
 * @endcode
 *
 * @note La precisi�n del retardo depende de la frecuencia del oscilador del microcontrolador. Aseg�rese de que la macro `__delay_us()` est� configurada correctamente para su configuraci�n de hardware.
 *
 * @remark La duraci�n del pulso en LATCH debe cumplir con las especificaciones del 74HC595 para asegurar una transferencia correcta de los datos. Consultar la hoja de datos del 74HC595 para obtener informaci�n precisa sobre los tiempos de latch.
 */
void latch(void);

#endif	/* XC_HEADER_TEMPLATE_H */

