/*
 * File:   main.c
 * Author: mmont
 *
 * Created on 25 de enero de 2025, 07:18 PM
 */

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
#define _XTAL_FREQ 4000000
#include <stdint.h>
#include <stdlib.h>
#include "lista.h"


Nodo* crearNodo(Sensor* sensor)
{
    Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));
    if(nodo == NULL)
    {
        return NULL;
    }
    nodo->siguiente = NULL;
    return nodo;
}

void destruirNodo(Nodo* nodo)
{
    free(nodo);
}

void inicializarLista(Lista* lista)
{
    lista->cabeza = NULL;
    lista->longitud = 0;
}

void insertarFinal(Lista* lista, Sensor* sensor)
{
    Nodo* nodo = crearNodo(sensor);
    if(lista->cabeza == NULL){
        lista->cabeza = nodo;
    }else{
        Nodo* puntero = lista->cabeza;
        while(puntero->siguiente){
            puntero = puntero->siguiente;
        }
    puntero->siguiente = nodo;   
    }
    lista->longitud++;
}

void liberarLista(Lista* lista)
{
    if(lista->cabeza)
    {
        Nodo* eliminado = lista->cabeza;
        Nodo* sig;
        while (eliminado!=NULL)
        {
            sig = eliminado->siguiente;
            destruirNodo(eliminado);
            eliminado = sig->siguiente;
        }
    }
}
void main(void) {
    Lista miLista;
   
    inicializarLista(&miLista);
    
    //Creando algunos sensores
    Sensor sensor1 = {0,210};
    Sensor sensor2 = {1,25};
    Sensor sensor3 = {2,67};
    Sensor sensor4 = {3,76};
    Sensor sensor5 = {4,76};
    
    insertarFinal(&miLista, &sensor1);
    insertarFinal(&miLista, &sensor2);
    insertarFinal(&miLista, &sensor3);
    insertarFinal(&miLista, &sensor4);
    insertarFinal(&miLista, &sensor5);
    
    //Recorriendo la lista para procesar datos
    Nodo* actual = miLista.cabeza;
    while(actual->siguiente)
    {
        //Este ejemplo enviar el valor del sensor por Serial
        //enviarRS232(actual->sensor->valor)
        actual = actual->siguiente;
    }
    liberarLista(&miLista);
    
}
