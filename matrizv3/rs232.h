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
 * @brief Inicializa el m�dulo USART (Universal Synchronous Asynchronous Receiver Transmitter) para la comunicaci�n RS-232 del PIC16F628A.
 *
 * @pre Ninguna.
 *
 * @details Esta funci�n configura el m�dulo USART del microcontrolador para la comunicaci�n as�ncrona RS-232 a una velocidad de 9600 bps. Realiza las siguientes configuraciones:
 *   1. Configura el registro `SPBRG` para la velocidad de baudios de 9600 bps.
 *   2. Configura el registro `TXSTA` para habilitar la transmisi�n as�ncrona.
 *   3. Configura el registro `RCSTA` para habilitar la recepci�n as�ncrona.
 *   4. Configura el pin RB1 como entrada (RX) y el pin RB2 como salida (TX).
 *
 * @code
 * init_rs232(); // Inicializa la comunicaci�n RS-232 a 9600 bps.
 * @endcode
 *
 * @note El valor de `SPBRG` (0x19) est� calculado para una frecuencia de oscilador espec�fica. Si la frecuencia del oscilador es diferente, este valor debe recalcularse. Consultar la hoja de datos del microcontrolador para obtener la f�rmula de c�lculo y los valores correspondientes.
 *
 * @remark Esta configuraci�n asume un modo de 8 bits de datos, sin paridad y 1 bit de stop. Para configuraciones diferentes (por ejemplo, con paridad), se deben modificar los registros `TXSTA` y `RCSTA` seg�n la hoja de datos del microcontrolador.
 */
void init_rs232(void);
/**
 * @brief Env�a un byte de datos a trav�s del puerto serial RS-232.
 *
 * @param dat Byte de datos que se va a enviar.
 *
 * @pre El m�dulo USART debe haber sido inicializado previamente con la funci�n `init_rs232()`.
 *
 * @details Esta funci�n env�a un byte de datos a trav�s del puerto serial RS-232. Utiliza el registro `TXREG` para transmitir los datos y el bit `TRMT` (Transmit Shift Register Empty) del registro `TXSTA` para verificar si el buffer de transmisi�n est� vac�o antes de enviar un nuevo byte. El proceso es el siguiente:
 *   1. Se entra en un bucle `while` que espera a que el bit `TRMT` est� a 1. Esto indica que el buffer de transmisi�n est� vac�o y listo para recibir un nuevo dato.
 *   2. Una vez que el buffer est� vac�o, se escribe el byte de datos `dat` en el registro `TXREG`. Esto inicia la transmisi�n del dato.
 *
 * @code
 * enviaRS232('A'); // Env�a el car�cter 'A'.
 * unsigned char myByte = 0x42;
 * enviaRS232(myByte); // Env�a el byte 0x42.
 * @endcode
 *
 * @note Esta funci�n bloquea la ejecuci�n del programa hasta que el buffer de transmisi�n est� vac�o. Si se necesita un manejo no bloqueante, se deben utilizar interrupciones o un enfoque diferente.
 *
 * @remark Es importante asegurarse de que el dispositivo receptor est� configurado con la misma velocidad de baudios y otros par�metros de comunicaci�n (bits de datos, paridad, bits de stop) que el transmisor.
 */
void enviaRS232(unsigned char dat);
/**
 * @brief Env�a una cadena de caracteres a trav�s del puerto serial RS-232.
 *
 * @param cad Puntero constante a la cadena de caracteres que se va a enviar.
 *
 * @pre El m�dulo USART debe haber sido inicializado previamente con la funci�n `init_rs232()`.
 *
 * @details Esta funci�n env�a una cadena de caracteres terminada en nulo a trav�s del puerto serial RS-232. Itera sobre la cadena car�cter por car�cter, utilizando la funci�n `enviaRS232()` para enviar cada car�cter individualmente. El bucle contin�a hasta que se encuentra el car�cter nulo ('\0'), que marca el final de la cadena.
 *
 * @code
 * printCad("Hola Mundo!"); // Env�a la cadena "Hola Mundo!".
 * const char myString[] = "Otro ejemplo";
 * printCad(myString); // Env�a la cadena "Otro ejemplo".
 * @endcode
 *
 * @note Esta funci�n depende de la funci�n `enviaRS232()`, que tiene un comportamiento bloqueante. Por lo tanto, `printCad()` tambi�n bloquear� la ejecuci�n del programa hasta que se haya enviado toda la cadena.
 *
 * @remark Es importante asegurarse de que la cadena `cad` est� correctamente terminada en nulo. De lo contrario, la funci�n podr�a intentar leer m�s all� del final de la cadena, lo que podr�a provocar un comportamiento indefinido.
 */
void printCad(const char *cad);
/**
 * @brief Env�a un byte como dos caracteres hexadecimales a trav�s del puerto serial RS-232.
 *
 * @param byte Byte que se va a enviar en formato hexadecimal.
 *
 * @pre El m�dulo USART debe haber sido inicializado previamente con la funci�n `init_rs232()`.
 *
 * @details Esta funci�n convierte un byte en su representaci�n hexadecimal de dos caracteres y los env�a a trav�s del puerto serial RS-232. El proceso es el siguiente:
 *   1. Se extrae el nibble alto (4 bits m�s significativos) del byte usando un desplazamiento a la derecha y una m�scara AND.
 *   2. Se verifica si el nibble es menor que 10.
 *     a. Si es menor que 10, se convierte a su representaci�n ASCII sum�ndole el c�digo ASCII del car�cter '0'.
 *     b. Si es mayor o igual a 10, se convierte a su representaci�n ASCII sum�ndole el c�digo ASCII del car�cter 'A' y rest�ndole 10.
 *   3. Se env�a el car�cter resultante a trav�s de la funci�n `enviaRS232()`.
 *   4. Se repiten los pasos 1-3 para el nibble bajo (4 bits menos significativos) del byte.
 *
 * @code
 * unsigned char myByte = 0xAF;
 * enviaHexByte(myByte); // Env�a los caracteres 'A' y 'F' a trav�s del puerto serial.
 * @endcode
 *
 * @note Esta funci�n depende de la funci�n `enviaRS232()`, que tiene un comportamiento bloqueante. Por lo tanto, `enviaHexByte()` tambi�n bloquear� la ejecuci�n del programa hasta que se hayan enviado los dos caracteres.
 *
 * @remark Esta funci�n utiliza caracteres ASCII '0'-'9' y 'A'-'F' para representar los valores hexadecimales.
 */
void enviaHexByte(unsigned char byte);

#endif	/* XC_HEADER_TEMPLATE_H */

