/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef RS232_H
#define	RS232_H

#include <xc.h> // include processor files - each processor file is guarded.  

/**
 * @brief Inicializa el módulo USART (Universal Synchronous Asynchronous Receiver Transmitter) para la comunicación RS-232 del PIC16F628A.
 *
 * @pre Ninguna.
 *
 * @details Esta función configura el módulo USART del microcontrolador para la comunicación asíncrona RS-232 a una velocidad de 9600 bps. Realiza las siguientes configuraciones:
 *   1. Configura el registro `SPBRG` para la velocidad de baudios de 9600 bps.
 *   2. Configura el registro `TXSTA` para habilitar la transmisión asíncrona.
 *   3. Configura el registro `RCSTA` para habilitar la recepción asíncrona.
 *   4. Configura el pin RB1 como entrada (RX) y el pin RB2 como salida (TX).
 *
 * @code
 * init_rs232(); // Inicializa la comunicación RS-232 a 9600 bps.
 * @endcode
 *
 * @note El valor de `SPBRG` (0x19) está calculado para una frecuencia de oscilador específica. Si la frecuencia del oscilador es diferente, este valor debe recalcularse. Consultar la hoja de datos del microcontrolador para obtener la fórmula de cálculo y los valores correspondientes.
 *
 * @remark Esta configuración asume un modo de 8 bits de datos, sin paridad y 1 bit de stop. Para configuraciones diferentes (por ejemplo, con paridad), se deben modificar los registros `TXSTA` y `RCSTA` según la hoja de datos del microcontrolador.
 */
void init_rs232(void);
/**
 * @brief Envía un byte de datos a través del puerto serial RS-232.
 *
 * @param dat Byte de datos que se va a enviar.
 *
 * @pre El módulo USART debe haber sido inicializado previamente con la función `init_rs232()`.
 *
 * @details Esta función envía un byte de datos a través del puerto serial RS-232. Utiliza el registro `TXREG` para transmitir los datos y el bit `TRMT` (Transmit Shift Register Empty) del registro `TXSTA` para verificar si el buffer de transmisión está vacío antes de enviar un nuevo byte. El proceso es el siguiente:
 *   1. Se entra en un bucle `while` que espera a que el bit `TRMT` esté a 1. Esto indica que el buffer de transmisión está vacío y listo para recibir un nuevo dato.
 *   2. Una vez que el buffer está vacío, se escribe el byte de datos `dat` en el registro `TXREG`. Esto inicia la transmisión del dato.
 *
 * @code
 * enviaRS232('A'); // Envía el carácter 'A'.
 * unsigned char myByte = 0x42;
 * enviaRS232(myByte); // Envía el byte 0x42.
 * @endcode
 *
 * @note Esta función bloquea la ejecución del programa hasta que el buffer de transmisión esté vacío. Si se necesita un manejo no bloqueante, se deben utilizar interrupciones o un enfoque diferente.
 *
 * @remark Es importante asegurarse de que el dispositivo receptor esté configurado con la misma velocidad de baudios y otros parámetros de comunicación (bits de datos, paridad, bits de stop) que el transmisor.
 */
void enviaRS232(unsigned char dat);
/**
 * @brief Envía una cadena de caracteres a través del puerto serial RS-232.
 *
 * @param cad Puntero constante a la cadena de caracteres que se va a enviar.
 *
 * @pre El módulo USART debe haber sido inicializado previamente con la función `init_rs232()`.
 *
 * @details Esta función envía una cadena de caracteres terminada en nulo a través del puerto serial RS-232. Itera sobre la cadena carácter por carácter, utilizando la función `enviaRS232()` para enviar cada carácter individualmente. El bucle continúa hasta que se encuentra el carácter nulo ('\0'), que marca el final de la cadena.
 *
 * @code
 * printCad("Hola Mundo!"); // Envía la cadena "Hola Mundo!".
 * const char myString[] = "Otro ejemplo";
 * printCad(myString); // Envía la cadena "Otro ejemplo".
 * @endcode
 *
 * @note Esta función depende de la función `enviaRS232()`, que tiene un comportamiento bloqueante. Por lo tanto, `printCad()` también bloqueará la ejecución del programa hasta que se haya enviado toda la cadena.
 *
 * @remark Es importante asegurarse de que la cadena `cad` esté correctamente terminada en nulo. De lo contrario, la función podría intentar leer más allá del final de la cadena, lo que podría provocar un comportamiento indefinido.
 */
void printCad(const char *cad);
/**
 * @brief Envía un byte como dos caracteres hexadecimales a través del puerto serial RS-232.
 *
 * @param byte Byte que se va a enviar en formato hexadecimal.
 *
 * @pre El módulo USART debe haber sido inicializado previamente con la función `init_rs232()`.
 *
 * @details Esta función convierte un byte en su representación hexadecimal de dos caracteres y los envía a través del puerto serial RS-232. El proceso es el siguiente:
 *   1. Se extrae el nibble alto (4 bits más significativos) del byte usando un desplazamiento a la derecha y una máscara AND.
 *   2. Se verifica si el nibble es menor que 10.
 *     a. Si es menor que 10, se convierte a su representación ASCII sumándole el código ASCII del carácter '0'.
 *     b. Si es mayor o igual a 10, se convierte a su representación ASCII sumándole el código ASCII del carácter 'A' y restándole 10.
 *   3. Se envía el carácter resultante a través de la función `enviaRS232()`.
 *   4. Se repiten los pasos 1-3 para el nibble bajo (4 bits menos significativos) del byte.
 *
 * @code
 * unsigned char myByte = 0xAF;
 * enviaHexByte(myByte); // Envía los caracteres 'A' y 'F' a través del puerto serial.
 * @endcode
 *
 * @note Esta función depende de la función `enviaRS232()`, que tiene un comportamiento bloqueante. Por lo tanto, `enviaHexByte()` también bloqueará la ejecución del programa hasta que se hayan enviado los dos caracteres.
 *
 * @remark Esta función utiliza caracteres ASCII '0'-'9' y 'A'-'F' para representar los valores hexadecimales.
 */
void enviaHexByte(unsigned char byte);

#endif	/* XC_HEADER_TEMPLATE_H */

