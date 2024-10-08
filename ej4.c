/*
Considerando pulsadores normalmente abiertos conectados en un extremo a
masa y en el otro directamente a las entradas P0.0 y p0.1. Realizar un programa
que identifique en una variable cual o cuales pulsadores han sido presionados.
Las identificaciones posibles a implementar en esta variable van a ser "ninguno",
"pulsador 1", "pulsador 2", "pulsador 1 y 2".
*/


#include "LPC17xx.h"

void PortConfig(void);



int main(void){

PortConfig();
While(1){
    if(!(LPC_GPIO0->FIOPIN & (1<<0)) && !(LPC_GPIO0->FIOPIN & (1<<1))){ //P0.0 and P0.1 btn activated
        char cadena[16] = "pulsador 1 y 2 presionados";
    }
    else if(!(LPC_GPIO0->FIOPIN & (1<<0)) && (LPC_GPIO0->FIOPIN & (1<<1))){
        char cadena[16] = "pulsador 1 presionado";
    }
    else if((LPC_GPIO0->FIOPIN & (1<<0)) && !(LPC_GPIO0->FIOPIN & (1<<1))){
        char cadena[16] = "pulsador 2 presionado";
    }
    else{
        char cadena[16] = "ninguno";
    }
}
return(0);
}


void PortConfig(void){
//PORT CONFIG:

LPC_PINCON->PINSEL0 &= ~(0xF<<0); //enable GPIO0 for P0.0 and P0.1

LPC_GPIO0->FIODIR |= ~(3<<0); //SET PIN 0-1 AS INPUT

LPC_PINCON->PINMODE0 |= ~(0xF<<0); //enable pull up resistor in P0.4

}