/*
Escribir un programa en C que permita sacar por los pines P1.16 al P1.23 el
equivalente en ascii de "a" si la interrupción se ha realizado por interrupción de
EINT1 y no hay interrupción pendiente de EINT0. Para el caso en el cual se
produzca una interrupción por EINT1 y exista una interrupción pendiente de
EINT0 sacar por el puerto el equivalente en ascii de "A". La interrupción de
EINT1 es por el flanco de subida producido por un pulsador identificado como
"tecla a/A", mientras que la interrupción EINT0 es por el nivel alto de un
pulsador etiquetado como "Activación de Mayusculas".
Nota: Valerse de la configuración de los niveles de prioridad para que la
pulsación conjunta de "Activación de Mayúsculas" con "tecla a/A" de como
resultado a la salida el equivalente en ascii "A".
*/


#include "LPC17xx.h"

void PortConfig(void);

uint16_t a= 0x61; //"a" en ascii
uint16_t A= 0x41; //"A" en ascii
int mayus = 0;

int main(void){

PortConfig();
While(1){   //loop
}

return(0);
}


void PortConfig(void){
//PORT CONFIG:
LPC_GPIO1->FIODIR2 |= (0xFF<<0);    //P1.16 to P1.23 as output

LPC_PINCON->PINSEL4 |= (0b0101<<20); //enable EINT1 & EINT0
NVIC_EnableIRQ(EINT1_EnableIRQn);
NVIC_EnableIRQ(EINT0_EnableIRQn);
NVIC_SetPriority(EINT1_IRQn, 5);    
NVIC_SetPriority(EINT0_IRQn, 3);    //EINT0 tendra mayor prioridad

LPC_SC->EXTMODE |= ~(1<<0); //enable EINT0 level sensitivity
LPC_SC->EXTPOLAR |= (1<<0); //HIGH LEVEL ACTIVATION

LPC_SC->EXTMODE |= (1<<1); //enable EINT1 edge sensitive
LPC_SC->EXTPOLAR |= (1<<1); //rising edge

LPC_SC->EXTINT |= (3<<0); //CLEAR INT FLAG FOR EINT1 & EINT0
}

EINT1_IRQHandler(void){
    if(!(LPC_SC->EXTINT) && (1<<0)){   // me aseguro que el mayus no este presionado
        LPC_GPIO1->FIOSET |= (a<<16);
    }
    LPC_SC->EXTINT |= (1<<1); //clear flag EINT1
}

EINT0_IRQHandler(void){ //mayus precionado
    if(LPC_SC->EXTINT && (1<<1)){   // tecla "a" precionada?
        LPC_GPIO1->FIOSET |= (A<<16);
        LPC_SC->EXTINT |= (1<<1); //clear flag EINT1
    }
}
