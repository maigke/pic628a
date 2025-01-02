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
 * @param cat Valor a enviar al primer registro 74HC595 (generalmente para los cátodos de un display).
 * @param an Valor a enviar al segundo registro 74HC595 (generalmente para los ánodos de un display).
 *
 * @pre Los pines DATA, CLOCK y LATCH deben estar configurados como salidas. Las funciones shift() y latch() deben estar definidas.
 *
 * @details Esta función envía dos valores a través de la función shift() a dos registros 74HC595 conectados en cascada. Primero se envía el valor 'an' y luego el valor 'cat'. Finalmente, se llama a la función latch() para transferir los datos a las salidas de los registros.
 *
 * @code
 * // Ejemplo de uso: enviar 0xFF al registro de cátodos y 0x01 al registro de ánodos.
 * H595(0xFF, 0x01);
 * @endcode
 *
 * @remark El orden en que se envían los datos (primero 'an' y luego 'cat') depende de la conexión física de los registros en cascada. Asegúrate de que este orden corresponda con tu hardware.
 */
void H595 (int cat , int an);

/**
 * @brief Realiza el desplazamiento de un valor bit a bit a través del pin DATA.
 *
 * @param val Valor entero de 8 bits a desplazar.
 * @param dir Dirección del desplazamiento:
 *            - 1: Desplazamiento a la derecha (MSB primero).
 *            - 0: Desplazamiento a la izquierda (LSB primero).
 *
 * @pre El pin DATA debe estar configurado como salida. La función clock() debe estar definida y generar un pulso de reloj.
 *
 * @return Ninguno.
 *
 * @details Esta función implementa un desplazamiento bit a bit de un valor entero de 8 bits a través del pin DATA. 
 *          Dependiendo del parámetro 'dir', el desplazamiento se realiza hacia la derecha (MSB primero) o hacia la izquierda (LSB primero).
 *          Después de cada bit enviado, se llama a la función clock() para generar un pulso de reloj.
 *
 * @code
 * // Ejemplo de uso: desplazar el valor 0b10101010 hacia la derecha
 * shift(0b10101010, 1);
 *
 * // Ejemplo de uso: desplazar el valor 0b01010101 hacia la izquierda
 * shift(0b01010101, 0);
 * @endcode
 *
 * @remark Es crucial que la función clock() genere un pulso de reloj con la duración correcta para el dispositivo receptor.
 */
void shift(int val,int dir);
/**
 * @brief Genera un pulso de reloj en el pin CLK.
 *
 * @pre El pin CLK debe estar configurado como salida.
 *
 * @details Esta función genera un pulso de reloj de onda cuadrada en el pin CLK. El pulso consiste en un flanco ascendente (CLK = 1) seguido de un retardo de 5 microsegundos, y luego un flanco descendente (CLK = 0) seguido de otro retardo de 5 microsegundos. Esto resulta en un ciclo completo de 10 microsegundos.
 *
 * @code
 * clock(); // Genera un pulso de reloj de 10 microsegundos.
 * @endcode
 *
 * @note La precisión del retardo depende de la frecuencia del oscilador del microcontrolador. Asegúrate de que la macro __delay_us() esté configurada correctamente para tu configuración de hardware.
 *
 * @remark Es importante que la duración del pulso de reloj sea compatible con las especificaciones del dispositivo al que se está enviando la señal de reloj (por ejemplo, el 74HC595).
 */
void clock(void);
/**
 * @brief Genera un pulso en el pin LATCH para transferir los datos a las salidas del registro 74HC595.
 *
 * @pre El pin LATCH debe estar configurado como salida.
 *
 * @details Esta función genera un pulso positivo (de bajo a alto y luego a bajo) en el pin LATCH. Este pulso transfiere los datos que se han desplazado previamente a través de la función `shift()` a las salidas del registro 74HC595. El pulso en alto tiene una duración de aproximadamente 10 microsegundos.
 *
 * @code
 * latch(); // Transfiere los datos a las salidas del registro 74HC595.
 * @endcode
 *
 * @note La precisión del retardo depende de la frecuencia del oscilador del microcontrolador. Asegúrese de que la macro `__delay_us()` esté configurada correctamente para su configuración de hardware.
 *
 * @remark La duración del pulso en LATCH debe cumplir con las especificaciones del 74HC595 para asegurar una transferencia correcta de los datos. Consultar la hoja de datos del 74HC595 para obtener información precisa sobre los tiempos de latch.
 */
void latch(void);

#endif	/* XC_HEADER_TEMPLATE_H */

