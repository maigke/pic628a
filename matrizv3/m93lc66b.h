/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef M93LC66B_H
#define	M93LC66B_H

#include <xc.h> // include processor files - each processor file is guarded.  
#define _XTAL_FREQ 4000000

// Definiciones de pines
// Interfaz 93LC66B
#define CS PORTAbits.RA0
#define SK PORTAbits.RA1
#define DI PORTAbits.RA2
#define DO PORTAbits.RA3
 
const unsigned char OPcode_Lectura = 0b00000010;
//Numero de elementos guardos en la EEPROM
//Este valor puede cambiar de acuerdo al numero de 
//patrones que hayan sido guardados
const unsigned char NUM_OF_CHARACTERS = 37;
unsigned int Buf; //variable que recibe el contenido de la memoria


/**
 * @brief Inicializa la EEPROM 93LC66B y configura los pines del microcontrolador.
 *
 * @pre Ninguna.
 *
 * @details Esta funci�n configura los pines del microcontrolador para la comunicaci�n con la EEPROM 93LC66B. Configura los pines RA0 (CS), RA1 (CLK) y RA2 (DI) como salidas, y el pin RA3 (DO) como entrada. Adem�s, deshabilita los comparadores anal�gicos configurando el registro CMCON.
 *
 * @code
 * init_93lc66b(); // Inicializa la EEPROM 93LC66B
 * @endcode
 *
 * @note Es crucial que los pines del microcontrolador se configuren correctamente para evitar conflictos y asegurar una comunicaci�n adecuada con la EEPROM.
 *
 * @remark La configuraci�n `CMCON = 0x07` deshabilita los comparadores anal�gicos en el PIC. Si necesitas usar los comparadores, deber�s modificar esta configuraci�n y asegurarte de que no interfieran con la comunicaci�n con la EEPROM.
 */
void init_93lc66b(void);

/**
 * @brief Lee 16 bits de datos desde un dispositivo externo utilizando un protocolo de desplazamiento.
 *
 * @pre Los pines SK (reloj) y DO (datos de entrada) deben estar configurados correctamente. El dispositivo externo debe estar enviando los datos sincronizados con la se�al de reloj.
 *
 * @details Esta funci�n implementa un protocolo de desplazamiento para leer 16 bits de datos desde un dispositivo externo. Funciona de la siguiente manera:
 *   1. Se inicializa una variable `myDataIn` a 0 para almacenar los datos recibidos.
 *   2. Se itera 16 veces (para leer 16 bits).
 *   3. En cada iteraci�n:
 *     a. Se pone el pin SK (reloj) a bajo.
 *     b. Se espera 1 microsegundo.
 *     c. Se lee el estado del pin DO (datos de entrada) y se guarda en la variable `temp`.
 *     d. Si `temp` es 1, se establece el bit correspondiente en `myDataIn` usando un OR bit a bit y un desplazamiento a la izquierda.
 *     e. Se pone el pin SK (reloj) a alto.
 *   4. Finalmente, se retorna el valor de `myDataIn`, que contiene los 16 bits le�dos.
 *
 * @return Un valor entero sin signo de 16 bits (`unsigned int`) que contiene los datos le�dos.
 *
 * @code
 * unsigned int receivedData = shiftIn16(); // Lee 16 bits de datos.
 * @endcode
 *
 * @note La precisi�n del retardo depende de la frecuencia del oscilador del microcontrolador. Aseg�rese de que la macro `__delay_us()` est� configurada correctamente para su configuraci�n de hardware.
 *
 * @remark Es crucial que el dispositivo externo genere una se�al de reloj y datos compatible con este protocolo de lectura. Consultar la hoja de datos del dispositivo externo para obtener informaci�n precisa sobre los tiempos y el protocolo de comunicaci�n. La variable `pinState` no es necesaria y puede ser eliminada para optimizar el c�digo.
 */
unsigned int shiftIn16();
/**
 * @brief Genera la secuencia de bits de inicio para la comunicaci�n con la EEPROM 93LC66B.
 *
 * @pre Los pines CS (Chip Select), SK (Clock) y DI (Data In) deben estar configurados como salidas.
 *
 * @details Esta funci�n genera la secuencia de bits necesaria para iniciar una comunicaci�n con la EEPROM 93LC66B. La secuencia consiste en los siguientes pasos:
 *   1. Se pone CS a bajo (selecci�n del chip).
 *   2. Se espera 1 microsegundo.
 *   3. Se pone SK a bajo.
 *   4. Se pone DI a bajo.
 *   5. Se pone CS a alto.
 *   6. Se espera 1 microsegundo.
 *   7. Se pone DI a alto.
 *   8. Se espera 1 microsegundo.
 *   9. Se genera un flanco de subida en SK (SK pasa a alto).
 *   10. Se espera 1 microsegundo.
 *   11. Se pone SK a bajo.
 *   12. Se espera 1 microsegundo.
 *
 * @code
 * startBit(); // Inicia la comunicaci�n con la EEPROM.
 * @endcode
 *
 * @note La precisi�n de los retardos depende de la frecuencia del oscilador del microcontrolador. Aseg�rese de que la macro `__delay_us()` est� configurada correctamente para su configuraci�n de hardware.
 *
 * @remark Esta secuencia de bits es espec�fica para la EEPROM 93LC66B y debe consultarse la hoja de datos para verificar los tiempos y la secuencia exacta. Un error en esta secuencia impedir� la correcta comunicaci�n con la EEPROM.
 */
void startBit(void);
/**
 * @brief Lee 16 bits de datos desde la EEPROM 93LC66B.
 *
 * @pre Los pines CS, SK y DO deben estar configurados correctamente. La EEPROM debe haber sido inicializada correctamente con la funci�n `init_93lc66b()`. Se debe haber enviado previamente el c�digo de operaci�n y la direcci�n de lectura.
 *
 * @details Esta funci�n lee 16 bits de datos desde la EEPROM 93LC66B utilizando la funci�n `shiftIn16()`. El valor le�do se almacena en la variable `Buffer` y se retorna.
 *
 * @return Un valor entero sin signo de 16 bits (`unsigned int`) que contiene los datos le�dos desde la EEPROM.
 *
 * @code
 * unsigned int data = leeMemoria(); // Lee 16 bits de datos desde la EEPROM.
 * @endcode
 *
 * @remark Esta funci�n asume que ya se ha enviado el c�digo de operaci�n de lectura y la direcci�n a la EEPROM. Consultar la hoja de datos de la 93LC66B para obtener informaci�n sobre el protocolo de comunicaci�n completo. El c�digo comentado `//Buffer = (Buffer >> 8) | (Buffer << 8);` se ha eliminado porque no se utiliza. Si se necesitara invertir el orden de los bytes, se deber�a volver a incluir y documentar adecuadamente.
 */
unsigned int leeMemoria();
/**
 * @brief Lee el valor de un bit espec�fico dentro de un dato de 16 bits.
 *
 * @param data Dato de 16 bits del cual se leer� el bit.
 * @param numeroBit N�mero del bit que se desea leer (0 para el bit menos significativo, 15 para el m�s significativo).
 *
 * @pre `numeroBit` debe estar dentro del rango v�lido de 0 a 15.
 *
 * @details Esta funci�n extrae el valor de un bit espec�fico dentro de un dato de 16 bits. Utiliza un desplazamiento a la derecha (`>>`) para mover el bit deseado a la posici�n menos significativa y luego una m�scara AND (`& 0x01`) para obtener su valor (0 o 1).
 *
 * @return Un valor de tipo `unsigned char` que representa el valor del bit le�do (0 o 1).
 *
 * @code
 * unsigned int myData = 0xABCD; // Dato de ejemplo
 * unsigned char bit5 = bitRead(myData, 5); // Lee el bit 5 (sexto bit desde la derecha)
 * unsigned char bit15 = bitRead(myData, 15); // Lee el bit 15 (bit m�s significativo)
 * @endcode
 *
 * @remark Es importante asegurarse de que el valor de `numeroBit` est� dentro del rango v�lido (0-15) para evitar comportamientos indefinidos.
 */
unsigned char bitRead(unsigned int data, unsigned char numeroBit);


/**
 * @brief Escribe una secuencia de bits en un dispositivo externo utilizando un protocolo de desplazamiento.
 *
 * @param dato Dato de 16 bits que se va a escribir.
 * @param contador N�mero de bits que se van a escribir.
 *
 * @pre Los pines SK (reloj) y DI (datos de entrada) deben estar configurados como salidas. `contador` debe estar dentro del rango de 1 a 16.
 *
 * @details Esta funci�n escribe una secuencia de bits desde la variable `dato` al pin `DI`, sincronizada con la se�al de reloj `SK`. El n�mero de bits que se escriben est� determinado por el par�metro `contador`. El proceso es el siguiente:
 *   1. Se itera mientras `contador` sea mayor que 0.
 *   2. En cada iteraci�n:
 *     a. Se espera 1 microsegundo.
 *     b. Se lee el bit correspondiente de `dato` usando la funci�n `bitRead()` y se escribe en el pin `DI`. El bit que se lee est� determinado por `(contador - 1)`.
 *     c. Se espera 1 microsegundo.
 *     d. Se genera un flanco de subida en `SK` (SK pasa a 1).
 *     e. Se espera 1 microsegundo.
 *     f. Se genera un flanco de bajada en `SK` (SK pasa a 0).
 *     g. Se espera 1 microsegundo.
 *     h. Se decrementa `contador`.
 *   3. Despu�s del bucle, se pone `DI` a 0.
 *
 * @code
 * unsigned int dataToWrite = 0x1234;
 * escribe(dataToWrite, 8); // Escribe los 8 bits menos significativos de dataToWrite.
 * escribe(dataToWrite, 16); // Escribe los 16 bits de dataToWrite.
 * @endcode
 *
 * @note La precisi�n de los retardos depende de la frecuencia del oscilador del microcontrolador. Aseg�rese de que la macro `__delay_us()` est� configurada correctamente para su configuraci�n de hardware.
 *
 * @remark Es fundamental que el dispositivo externo est� configurado para recibir datos con este mismo protocolo de desplazamiento. Consultar la hoja de datos del dispositivo externo para obtener informaci�n precisa sobre los tiempos y el protocolo de comunicaci�n. El �ltimo paso de poner `DI` a 0 podr�a no ser necesario dependiendo del protocolo espec�fico del dispositivo.
 */
void escribe(unsigned int dato, unsigned char contador);
/**
 * @brief Lee un rango de direcciones de la EEPROM 93LC66B de forma autom�tica.
 *
 * @param inicio Direcci�n de inicio de la lectura.
 * @param alcance Direcci�n final de la lectura.
 *
 * @pre Los pines CS, SK y DO deben estar configurados correctamente. La EEPROM debe haber sido inicializada correctamente con la funci�n `init_93lc66b()`. `OPcode_Lectura` debe estar definido con el c�digo de operaci�n correcto para la lectura. `inicio` y `alcance` deben ser direcciones v�lidas dentro del rango de la EEPROM. `alcance` debe ser mayor o igual a `inicio`.
 *
 * @details Esta funci�n lee un rango de direcciones consecutivas de la EEPROM 93LC66B. El proceso es el siguiente:
 *   1. Se inicializa la variable `direccion` con el valor de `inicio`.
 *   2. Se genera la secuencia de inicio con `startBit()`.
 *   3. Se escribe el c�digo de operaci�n de lectura (`OPcode_Lectura`) con `escribe()`. Se escriben 2 bits para el c�digo de operaci�n.
 *   4. Se escribe la direcci�n de inicio (`direccion`) con `escribe()`. Se escriben 9 bits para la direcci�n.
 *   5. Se verifica si `alcance` es mayor que `direccion`.
 *   6. Si `alcance` es mayor que `direccion` (lectura de un rango):
 *     a. Se entra en un bucle `while` que se ejecuta mientras `direccion` sea menor o igual a `alcance`.
 *     b. Dentro del bucle:
 *       i. Se lee el dato de la direcci�n actual con `leeMemoria()` y se guarda en `Buf`.
 *       ii. Se espera 10 milisegundos.
 *       iii. Se asegura que `SK` est� en bajo.
 *       iv. Se espera 1 microsegundo.
 *       v. Se pone `DI` a 0.
 *       vi. Se incrementa `direccion`.
 *   7. Si `alcance` no es mayor que `direccion` (lectura de una sola direcci�n, lo cual es un caso que no deber�a ocurrir dado que se espera que alcance sea mayor o igual a inicio):
 *      a. Se lee el dato de la direcci�n actual con `leeMemoria()` y se guarda en `Buf`.
 *      b. Se espera 10 milisegundos.
 *      c. Se asegura que `SK` est� en bajo.
 *      d. Se espera 1 microsegundo.
 *      e. Se pone `DI` a 0.
 *
 * @code
 * leeAutomatico(0x00, 0x0F); // Lee desde la direcci�n 0x00 hasta la 0x0F.
 * @endcode
 *
 * @note La precisi�n de los retardos depende de la frecuencia del oscilador del microcontrolador. Aseg�rese de que las macros `__delay_ms()` y `__delay_us()` est�n configuradas correctamente para su configuraci�n de hardware. `Buf` debe ser una variable global o accesible dentro del �mbito de esta funci�n.
 *
 * @remark Es fundamental que el valor de `alcance` sea mayor o igual a `inicio`. De lo contrario, el comportamiento no ser� el esperado. Consultar la hoja de datos de la 93LC66B para obtener informaci�n precisa sobre el protocolo de comunicaci�n completo. El c�digo asume que la EEPROM est� configurada para palabras de 16 bits.
 */
void leeAutomatico(unsigned int inicio, int alcance);
/**
 * @brief Lee una palabra de 16 bits desde una direcci�n espec�fica de la EEPROM 93LC66B.
 *
 * @param direccion Direcci�n de memoria de la EEPROM desde la que se leer� la palabra.
 *
 * @pre Los pines CS, SK y DO deben estar configurados correctamente. La EEPROM debe haber sido inicializada correctamente con la funci�n `init_93lc66b()`. `OPcode_Lectura` debe estar definido con el c�digo de operaci�n correcto para la lectura. `direccion` debe ser una direcci�n v�lida dentro del rango de la EEPROM.
 *
 * @details Esta funci�n realiza una lectura de una palabra de 16 bits desde una direcci�n espec�fica de la EEPROM 93LC66B. El proceso es el siguiente:
 *   1. Se genera la secuencia de inicio con `startBit()`.
 *   2. Se escribe el c�digo de operaci�n de lectura (`OPcode_Lectura`) utilizando la funci�n `escribe()`. Se escriben 2 bits para el c�digo de operaci�n.
 *   3. Se escribe la direcci�n de memoria (`direccion`) utilizando la funci�n `escribe()`. Se escriben 9 bits para la direcci�n.
 *   4. Se leen los datos de la EEPROM utilizando la funci�n `leeMemoria()` y se guardan en la variable `data`.
 *   5. Se espera 10 milisegundos.
 *   6. Se asegura que el pin `SK` est� en bajo.
 *   7. Se espera 1 microsegundo.
 *   8. Se pone el pin `DI` a bajo.
 *   9. Se retorna el valor le�do (`data`).
 *
 * @return Un valor entero sin signo de 16 bits (`unsigned int`) que contiene la palabra le�da desde la EEPROM.
 *
 * @code
 * unsigned int dataRead = lee93LC66B(0x0A); // Lee la palabra en la direcci�n 0x0A.
 * @endcode
 *
 * @note La precisi�n de los retardos depende de la frecuencia del oscilador del microcontrolador. Aseg�rese de que las macros `__delay_ms()` y `__delay_us()` est�n configuradas correctamente para su configuraci�n de hardware.
 *
 * @remark Consultar la hoja de datos de la 93LC66B para obtener informaci�n precisa sobre el protocolo de comunicaci�n completo, incluyendo los tiempos de acceso y los c�digos de operaci�n. El c�digo asume que la EEPROM est� configurada para palabras de 16 bits.
 */
unsigned int lee93LC66B(unsigned int direccion);

#endif	/* XC_HEADER_TEMPLATE_H */

