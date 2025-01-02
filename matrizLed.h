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
 * @brief Busca la dirección en la EEPROM 93LC66B donde se encuentra almacenado un carácter específico.
 *
 * @param dat Carácter que se va a buscar en la EEPROM.
 *
 * @pre Los módulos de la EEPROM 93LC66B (`m93lc66b.h`), los registros de desplazamiento (`h595.h`) y la comunicación RS-232 (`rs232.h`) deben haber sido inicializados correctamente. `NUM_OF_CHARACTERS` debe estar definido como el número total de caracteres almacenados en la EEPROM. Se asume que los caracteres están almacenados en palabras de 16 bits, donde solo se utiliza el byte menos significativo (LSB). Los datos deben estar almacenados en direcciones multiplos de 10.
 *
 * @details Esta función busca la dirección en la EEPROM 93LC66B donde se encuentra almacenado el carácter `dat`. Realiza una búsqueda lineal en la EEPROM, leyendo palabras de 16 bits desde direcciones que son múltiplos de 10. Extrae el byte menos significativo (LSB) de cada palabra leída y lo compara con el carácter `dat`. Si se encuentra una coincidencia, la función retorna la dirección correspondiente.
 *
 * El proceso es el siguiente:
 *   1. Se inicializa un bucle `for` que itera desde 0 hasta `NUM_OF_CHARACTERS - 1`.
 *   2. En cada iteración:
 *     a. Se calcula la dirección de memoria actual como `10 * i`.
 *     b. Se lee una palabra de 16 bits desde la dirección calculada utilizando la función `lee93LC66B()`.
 *     c. Se extrae el byte menos significativo (LSB) de la palabra leída utilizando una máscara AND (`& 0x00FF`).
 *     d. Se compara el LSB extraído con el carácter `dat`.
 *     e. Si hay una coincidencia, se retorna la dirección actual (`10 * i`).
 *   3. Si no se encuentra ninguna coincidencia después de iterar sobre todos los caracteres almacenados, la función retorna 5.
 *
 * @return Un valor entero sin signo de 16 bits (`unsigned int`) que representa la dirección de la EEPROM donde se encontró el carácter `dat`. Si no se encuentra el carácter, retorna 5.
 *
 * @code
 * char charToFind = 'X';
 * unsigned int address = buscaDirEEPROM(charToFind);
 * if (address != 5) {
 *     // Se encontró el carácter en la dirección 'address'.
 * } else {
 *     // No se encontró el carácter.
 * }
 * @endcode
 *
 * @note El valor de retorno 5 en caso de no encontrar el carácter es arbitrario y podría ser modificado. Es importante que este valor sea un valor que no corresponda a una dirección válida de la EEPROM, para poder diferenciar entre una dirección válida y un error de búsqueda.
 *
 * @remark Esta función asume que los caracteres están almacenados en el byte menos significativo (LSB) de palabras de 16 bits en la EEPROM y que las direcciones de almacenamiento son multiplos de 10. Consultar la hoja de datos de la 93LC66B para obtener información precisa sobre la organización de la memoria y el protocolo de comunicación.
 */
unsigned int buscaDirEEPROM(char dat);
/**
 * @brief Muestra una cadena de caracteres en un display utilizando datos almacenados en la EEPROM 93LC66B.
 *
 * @param cad Puntero constante a la cadena de caracteres que se va a mostrar.
 *
 * @pre Los módulos de la EEPROM 93LC66B (`m93lc66b.h`), los registros de desplazamiento (`h595.h`) y la comunicación RS-232 (`rs232.h`) deben haber sido inicializados correctamente. `NUM_OF_CHARACTERS` debe estar definido. La función `buscaDirEEPROM()` debe estar implementada correctamente. Se asume que los datos en la EEPROM están organizados de la siguiente manera: en la dirección obtenida por `buscaDirEEPROM()` se almacena el número de patrones (bytes) que definen el carácter, y a partir de la dirección `dir + 2` se almacenan los patrones de 8 bits.
 *
 * @details Esta función toma una cadena de caracteres y la muestra en un display utilizando datos almacenados en la EEPROM 93LC66B. Por cada carácter en la cadena:
 *   1. Se busca la dirección en la EEPROM donde se almacenan los datos del carácter utilizando la función `buscaDirEEPROM()`.
 *   2. Si se encuentra la dirección (es decir, `buscaDirEEPROM()` no retorna 5):
 *     a. Se lee el número de patrones desde la EEPROM en la dirección obtenida y se guarda en `numPatrones`.
 *     b. Se leen los patrones del carácter desde la EEPROM, a partir de la dirección `dir + 2`, y se almacenan en el array `message`. Se leen los datos en pares, asumiendo que cada par representa un patrón.
 *     c. Se itera 32 veces para actualizar el display.
 *     d. Dentro de este bucle, se itera 8 veces, enviando cada byte del patrón a los registros de desplazamiento usando la función `H595()` y los valores del array `S`. Se genera un pequeño retardo entre cada envío.
 *   3. Se repiten los pasos 1 y 2 para el siguiente carácter de la cadena hasta que se encuentra el carácter nulo ('\0').
 *
 * @code
 * printCad93LC66B("Ejemplo"); // Muestra la cadena "Ejemplo" en el display.
 * @endcode
 *
 * @note La precisión de los retardos depende de la frecuencia del oscilador del microcontrolador. Asegúrese de que la macro `__delay_us()` esté configurada correctamente para su configuración de hardware. El tamaño del array `message` (10) debe ser lo suficientemente grande para almacenar el máximo número de patrones que se puedan leer desde la EEPROM.
 *
 * @remark Esta función asume una organización específica de los datos en la EEPROM. Consultar la documentación del formato de almacenamiento en la EEPROM para asegurar la compatibilidad. La constante `S` se utiliza para multiplexar los datos en el display. El valor 5 retornado por `buscaDirEEPROM` indica que el caracter no se encontro.
 */
void printCad93LC66B(const char *cad);



#endif	/* XC_HEADER_TEMPLATE_H */

