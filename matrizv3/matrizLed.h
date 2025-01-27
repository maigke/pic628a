/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MATRIZLED_H
#define	MATRIZLED_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "m93lc66b.h"
#include "h595.h"
#include "rs232.h"
/**
 * @brief Busca la direcci�n en la EEPROM 93LC66B donde se encuentra almacenado un car�cter espec�fico.
 *
 * @param dat Car�cter que se va a buscar en la EEPROM.
 *
 * @pre Los m�dulos de la EEPROM 93LC66B (`m93lc66b.h`), los registros de desplazamiento (`h595.h`) y la comunicaci�n RS-232 (`rs232.h`) deben haber sido inicializados correctamente. `NUM_OF_CHARACTERS` debe estar definido como el n�mero total de caracteres almacenados en la EEPROM. Se asume que los caracteres est�n almacenados en palabras de 16 bits, donde solo se utiliza el byte menos significativo (LSB). Los datos deben estar almacenados en direcciones multiplos de 10.
 *
 * @details Esta funci�n busca la direcci�n en la EEPROM 93LC66B donde se encuentra almacenado el car�cter `dat`. Realiza una b�squeda lineal en la EEPROM, leyendo palabras de 16 bits desde direcciones que son m�ltiplos de 10. Extrae el byte menos significativo (LSB) de cada palabra le�da y lo compara con el car�cter `dat`. Si se encuentra una coincidencia, la funci�n retorna la direcci�n correspondiente.
 *
 * El proceso es el siguiente:
 *   1. Se inicializa un bucle `for` que itera desde 0 hasta `NUM_OF_CHARACTERS - 1`.
 *   2. En cada iteraci�n:
 *     a. Se calcula la direcci�n de memoria actual como `10 * i`.
 *     b. Se lee una palabra de 16 bits desde la direcci�n calculada utilizando la funci�n `lee93LC66B()`.
 *     c. Se extrae el byte menos significativo (LSB) de la palabra le�da utilizando una m�scara AND (`& 0x00FF`).
 *     d. Se compara el LSB extra�do con el car�cter `dat`.
 *     e. Si hay una coincidencia, se retorna la direcci�n actual (`10 * i`).
 *   3. Si no se encuentra ninguna coincidencia despu�s de iterar sobre todos los caracteres almacenados, la funci�n retorna 5.
 *
 * @return Un valor entero sin signo de 16 bits (`unsigned int`) que representa la direcci�n de la EEPROM donde se encontr� el car�cter `dat`. Si no se encuentra el car�cter, retorna 5.
 *
 * @code
 * char charToFind = 'X';
 * unsigned int address = buscaDirEEPROM(charToFind);
 * if (address != 5) {
 *     // Se encontr� el car�cter en la direcci�n 'address'.
 * } else {
 *     // No se encontr� el car�cter.
 * }
 * @endcode
 *
 * @note El valor de retorno 5 en caso de no encontrar el car�cter es arbitrario y podr�a ser modificado. Es importante que este valor sea un valor que no corresponda a una direcci�n v�lida de la EEPROM, para poder diferenciar entre una direcci�n v�lida y un error de b�squeda.
 *
 * @remark Esta funci�n asume que los caracteres est�n almacenados en el byte menos significativo (LSB) de palabras de 16 bits en la EEPROM y que las direcciones de almacenamiento son multiplos de 10. Consultar la hoja de datos de la 93LC66B para obtener informaci�n precisa sobre la organizaci�n de la memoria y el protocolo de comunicaci�n.
 */
unsigned int buscaDirEEPROM(char dat);
/**
 * @brief Muestra una cadena de caracteres en un display utilizando datos almacenados en la EEPROM 93LC66B.
 *
 * @param cad Puntero constante a la cadena de caracteres que se va a mostrar.
 *
 * @pre Los m�dulos de la EEPROM 93LC66B (`m93lc66b.h`), los registros de desplazamiento (`h595.h`) y la comunicaci�n RS-232 (`rs232.h`) deben haber sido inicializados correctamente. `NUM_OF_CHARACTERS` debe estar definido. La funci�n `buscaDirEEPROM()` debe estar implementada correctamente. Se asume que los datos en la EEPROM est�n organizados de la siguiente manera: en la direcci�n obtenida por `buscaDirEEPROM()` se almacena el n�mero de patrones (bytes) que definen el car�cter, y a partir de la direcci�n `dir + 2` se almacenan los patrones de 8 bits.
 *
 * @details Esta funci�n toma una cadena de caracteres y la muestra en un display utilizando datos almacenados en la EEPROM 93LC66B. Por cada car�cter en la cadena:
 *   1. Se busca la direcci�n en la EEPROM donde se almacenan los datos del car�cter utilizando la funci�n `buscaDirEEPROM()`.
 *   2. Si se encuentra la direcci�n (es decir, `buscaDirEEPROM()` no retorna 5):
 *     a. Se lee el n�mero de patrones desde la EEPROM en la direcci�n obtenida y se guarda en `numPatrones`.
 *     b. Se leen los patrones del car�cter desde la EEPROM, a partir de la direcci�n `dir + 2`, y se almacenan en el array `message`. Se leen los datos en pares, asumiendo que cada par representa un patr�n.
 *     c. Se itera 32 veces para actualizar el display.
 *     d. Dentro de este bucle, se itera 8 veces, enviando cada byte del patr�n a los registros de desplazamiento usando la funci�n `H595()` y los valores del array `S`. Se genera un peque�o retardo entre cada env�o.
 *   3. Se repiten los pasos 1 y 2 para el siguiente car�cter de la cadena hasta que se encuentra el car�cter nulo ('\0').
 *
 * @code
 * printCad93LC66B("Ejemplo"); // Muestra la cadena "Ejemplo" en el display.
 * @endcode
 *
 * @note La precisi�n de los retardos depende de la frecuencia del oscilador del microcontrolador. Aseg�rese de que la macro `__delay_us()` est� configurada correctamente para su configuraci�n de hardware. El tama�o del array `message` (10) debe ser lo suficientemente grande para almacenar el m�ximo n�mero de patrones que se puedan leer desde la EEPROM.
 *
 * @remark Esta funci�n asume una organizaci�n espec�fica de los datos en la EEPROM. Consultar la documentaci�n del formato de almacenamiento en la EEPROM para asegurar la compatibilidad. La constante `S` se utiliza para multiplexar los datos en el display. El valor 5 retornado por `buscaDirEEPROM` indica que el caracter no se encontro.
 */
void printCad93LC66B(const char *cad);



#endif	/* XC_HEADER_TEMPLATE_H */

