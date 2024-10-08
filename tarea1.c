/*
===============================================================================
 Name        : Ejercicio1
 Author      : Alejo Beierbach
 Version     :
 Description : Una famosa empresa de calzados a incorporado a sus zapatillas 10 luces leds
comandadas por un microcontrolador LPC1769 y ha pedido a su grupo de
ingenieros que diseñen 2 secuencias de luces que cada cierto tiempo se vayan
intercalando (secuencia A - secuencia B- secuencia A- ... ). Como todavía no se
ha definido la frecuencia a la cual va a funcionar el CPU del microcontrolador, las
funciones de retardos que se incorporen deben tener como parametros de
entrada variables que permitan modificar el tiempo de retardo que se vaya a
utilizar finalmente. Se pide escribir el código que resuelva este pedido,
considerando que los leds se encuentran conectados en los puertos P0,0 al P0.9
===============================================================================
*/

#include "LPC17xx.h"


void delay(int tiempo){
    for(int i=0; i<tiempo; i++){

    }
}		

int main(void) {

// Enable GPIO
LPC_PINCON->PINSEL0 &= ~(0xFFFFF<<0); //con el AND logro poner en 0 el bit 0-18 sin afectar los otros bits
									//Enable GPIO in P0.0 to P0.9

// In/Out
LPC_GPIO0->FIODIR0 |= (0xFF<<0);	//Enables P0.0-P0.9 as output
LPC_GPIO0->FIODIR1 |= (0b11<<8);

while(1){ //Bucle infinito
    //Sequence A:
    LPC_GPIO0->FIOPIN  = (0x03FF); //turn on all LEDs
    delay(500);
    LPC_GPIO0->FIOPIN  = (0x0000); //turn off all LEDs
    delay(500);
    //Sequence B:
    LPC_GPIO0->FIOPIN  = (0x01AA); //turn on all LEDs
    delay(500);
    LPC_GPIO0->FIOPIN  = (0x0000); //turn off all LEDs
    delay(500);
	}

	return 0 ;
}

