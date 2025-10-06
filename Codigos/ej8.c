/*
 Configurar la interrupción externa EINT1 para que interrumpa por flanco de
bajada y la interrupción EINT2 para que interrumpa por flanco de subida. En la
interrupción por flanco de bajada configurar el systick para desbordar cada 25
mseg, mientras que en la interrupción por flanco de subida configurarlo para que
desborde cada 60 mseg. Considerar que EINT1 tiene mayor prioridad que EINT2
*/


#include "LPC17xx.h"

void PortConfig(void);
int INT1 = 0;
int INT2 = 0;
uint16_t contador1 = 5;
uint16_t contador2 = 12;    //12 veces para que el contador cuente 60ms



int main(void){

PortConfig();

While(1){   //loop
}

return(0);
}


void PortConfig(void){
//PORT CONFIG:

LPC_PINCON->PINSEL4 |= (0b0101<<22); //enable EINT1 & EINT2
NVIC_EnableIRQ(EINT1_EnableIRQn);
NVIC_EnableIRQ(EINT2_EnableIRQn);
NVIC_SetPriority(EINT1_IRQn, 4);
NVIC_SetPriority(EINT2_IRQn, 5);

LPC_SC->EXTMODE |= (3<<1); //enable EINT1 EINT2 edge sensitive
LPC_SC->EXTPOLAR |= ~(1<<1); //falling edge
LPC_SC->EXTPOLAR |= (1<<2); //RISING EDGE
LPC_SC->EXTINT |= (3<<1); //CLEAR INT FLAG FOR EINT1 & EINT2

//LPC_GPIO0->FIODIR |= ~(3<<0); //SET PIN 0-1 AS INPUT
}

EINT1_IRQHandler(void){
    INT1 = 1;
    INT2 = 0;   //to ensure the value
    LPC_SC->EXTINT |= (1<<1); //CLEAR INT FLAG FOR EINT1
    SystickLoad();
}
EINT2_IRQHandler(void){
    INT2 = 1;
    INT1 = 0;   //to ensure the value
    LPC_SC->EXTINT |= (2<<1); //CLEAR INT FLAG FOR EINT2
    SystickLoad();
}

SystickLoad(void){
    Systick->CTRL |= (0b111<<0); //enable counter,int and clk source
    Systick->LOAD = (0x7A11F);  // Load=(FrecCore * 5ms)-1=(100MHz * 5ms)-1= 499999
    Systick->VAL = 0; //Systick needs to reset counter
}

Systick_Handler(void){
    if(INT1 && !INT2){
        if(contador1!=0){
        contador1-=1;
        SystickLoad();
        }
    }
    if(!INT1 && INT2){
        if(contador2!=0){
        contador2-=1;
        SystickLoad();
        }
    }
}
