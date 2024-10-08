/*
Configure el Systick Timer de modo que genere una forma de onda llamada PWM
tal como la que se muestra en la figura adjunta. Esta señal debe ser sacada por el
pin P0.22 para que controle la intensidad de brillo del led. El periodo de la señal
debe ser de 10 mseg con un duty cycle de 10%. Configure la interrupción externa
EINT0 de modo que cada vez que se entre en una rutina de interrupción externa el
duty cycle incremente en un 10% (1 mseg). Esto se repite hasta llegar al 100%,
luego, si se entra nuevamente a la interrupción externa, el duty cycle volverá al 10%
*/

#include "LPC17xx.h"

void PortConfig(void);
void SystickConfig(void);
void encender(void);
void apagar(void)
int ciclos1ms = 0;  //cuenta las veces que sucedieron ciclos de 1ms
int EINT0_count = 0;    //cuenta las veces que se interrumpio por EINT0



int main(void){

PortConfig();
SystickConfig();
While(1){}

return(0);
}


void PortConfig(void){
//PORT CONFIG:

LPC_PINCON->PINSEL1 &= ~(3<<12); //enable GPIO0 for P0.22
LPC_GPIO0->FIODIR2 |= (1<<6); //SET PIN P0.22 AS OUTPUT

LPC_PINCON->PINSEL4 &= (0b01<<20); //enable EINT0
LPC_SC->EXTMODE |= (1<<0);   //edge level sensitive
LPC_SC->EXTPOLAR |= (1<<0);  //HIGH RISING
LPC_SC->EXTINT |= (1<<0);    //CLEAR INT FLAG
NVIC_EnableIRQ(EINT0_IRQn);
NVIC_SetPriority(EINT0_IRQn, 3);

encender(); //arrancar con la señal en alto

}

void SystickConfig(void);{
    Systick->CTRL |= (0b111<<0);
    Systick->LOAD = ((SystemCoreClock*0.001)-1); //0.001 = 1ms
    Systick->VAL = 0;   //Systick needs to restart
}

Systick_Handler(void){
    if(ciclos1ms<10){
        ciclos1ms+=1;
            if((ciclos1ms<=EINT0_count)){
                encender();
            }else{
                apagar();
            }
    }
    else if(ciclos1ms==10){
        encender();
        ciclos1ms = 0;  //reinicio el contador
    }
    SystickConfig();
    Systick->CTRL &= Systick->CTRL  //clear systick flag
}

EINT0_IRQHandler(void){
    if(EINT0_count<10){
        EINT0_count+=1;
    }else{
        EINT0_count=0;
    }
    LPC_SC->EXTINT |= (1<<0);    //CLEAR INT FLAG
}

void encender(void){
    LPC_GPIO0->FIOSET |= (1<<22)
}
void apagar(void){
    LPC_GPIO0->FIOSET |= ~(1<<22)
}