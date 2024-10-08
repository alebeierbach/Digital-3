/*Realizar un programa que configure el puerto P2.0 y P2.1 para que provoquen
una interrupción por flanco de subida para el primer pin y por flanco de bajada
para el segundo. Cuando la interrupción sea por P2.0 se enviará por el pin P0.0 la
secuencia de bits 010011010. Si la interrupción es por P2.1 se enviará por el pin
P0.1 la secuencia 011100110. Las secuencias se envían únicamente cuando se
produce una interrupción, en caso contrario la salida de los pines tienen valores 1
lógicos. ¿que prioridad tienen configuradas por defecto estas interrupciones?*/


#include "LPC17xx.h"

void PortConfig(void);
void EINTConfigP2(void);
int secuencia1[9] = {0, 1, 0, 0, 1, 1, 0, 1, 0};    //P0.0
int secuencia2[9] = {0, 1, 1, 1, 0. 0, 1, 1, 0};    //P0.1


int main(void){

PortConfig();
EINTConfigP2();

While(1){}

return(0);
}


void PortConfig(void){
//PORT CONFIG:

LPC_PINCON->PINSEL0 &= ~(0xF<<0); //enable GPIO0 for P0.0 and P0.1

LPC_GPIO0->FIODIR |= (3<<0); //SET PIN 0-1 AS OUTPUT
LPC_GPIO2->FIODIR |= ~(3<<0); //SET PIN 0-1 AS input        GPIO2

// LPC_PINCON->PINMODE0 |= ~(0xF<<0); //enable pull up resistor in P0.0 AND P0.1

}

void EINTConfigP2(void){

    LPC_GPIOINT->IO2IntEnR |= (1<<0); //enable P2.0 interrupt on rising edge
    LPC_GPIOINT->IO2IntEnF |= (1<<1); //enable P2.1 interrupt on falling edge
    NVIC_EnableIRQ(EINT3_IRQn);

}


EINT3_IRQHandler(void){

if(LPC_GPIOINT->IO2IntStatR && (1<<0)){ //interrupcion en P2.0 por flanco de subida
    for(int i=0; i<9; i++){
        if(secuencia1[i]){
            LPC_GPIO0->FIOSET |= (1<<0)
        } else{
            LPC_GPIO0->FIOSET |= ~(1<<0)
        }
    }
    LPC_GPIOINT->IO2IntClr |= (1<<1);   //clear interrupt flag
}

if(LPC_GPIOINT->IO2IntStatF && (1<<1)){ //interrupcion en P2.1 por flanco de bajada
    for(int i=0; i<9; i++){
        if(secuencia2[i]){
            LPC_GPIO0->FIOSET |= (1<<1)
        } else{
            LPC_GPIO0->FIOSET |= ~(1<<1)
        }
    }
    LPC_GPIOINT->IO2IntClr |= (1<<0);   //clear interrupt flag
}
}

