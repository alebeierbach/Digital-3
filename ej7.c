/*
Realizar un programa que configure el puerto P0.0 y P2.0 para que provoquen
una interrupción por flanco de subida. Si la interrupción es por P0.0 guardar el
valor binario 100111 en la variable "auxiliar", si es por P2.0 guardar el valor
binario 111001011010110
*/


#include "LPC17xx.h"

uint32_t auxiliar=0;
void INT0init(void);
void INT1init(void);
void PortConfig(void);


int main(void){

PortConfig();
INT0init();
INT2init();

While(1){

}
return(0);
}

void PortConfig(void){
//PORT CONFIG:
LPC_PINCON->PINSEL0 &= ~(3<<0); //enable GPIO0 for P0.0 and P0.1
LPC_PINCON->PINSEL4 &= ~(3<<0); //enable GPIO0 for P2.0

LPC_GPIO0->FIODIR &= ~(1<<0); //SET PIN 0 AS input        GPIO1
LPC_GPIO2->FIODIR &= ~(1<<0); //SET PIN 0 AS input        GPIO2

}

void INT0init(void){
    LPC_GPIOINT->IO0IntEnR |= (1<<0);       //enable interrupt on rising edge for P0.0
    NVIC_EnableIRQ(EINT3_IRQn);
}
void INT2init(void){
    LPC_GPIOINT->IO2IntEnR |= (1<<0);       //enable interrupt on rising edge for P2.0
    NVIC_EnableIRQ(EINT3_IRQn);
}


EINT3_IRQHandler(void){

    if(LPC_GPIOINT->IO2IntStatR && (1<<0)){
        auxiliar = 0b111001011010110;
        LPC_GPIOINT->IO2IntClr |= (1<<0);   //clear interrupt flag
    }else{
        auxiliar = 0b100111;
        LPC_GPIOINT->IO0IntClr |= (1<<0);   //Clear interrupt flag
    }
}

