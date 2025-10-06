/* Configurar el pin P0.4 como entrada digital con resistencia de pull down y
utilizarlo para decidir si el valor representado por los pines P0.0 al P0.3 van a ser
sumados o restados al valor guardado en la variable "acumulador".El valor inicial
de "acumulador" es 0
 */



#include "LPC17xx.h"

uint32_t acumulador=0;
uint32_t aux1=0;
void PortConfig(void);



int main(void){

PortConfig();

    While(1){
        //P0.4: 1 sumo y 0 resto

        aux1= LPC_GPIO0->FIOPIN & (0xF)     //select p0.0 to p0.3

        if(LPC_GPIO0->FIOPIN & (1<<4)){     // P0.4 is 1?
        acumulador+= aux1;
        }
        else{   //P0.4 is 0
            acumulador-= aux1;
        }
    }
    return(0);
}






void PortConfig(void){
//PORT CONFIG:

LPC_PINCON->PINSEL0 &= ~(0x3FF<<0); //PORT 0.0 TO 0.4 AS GPIO

LPC_GPIO0->FIODIR |= ~(0xF<<0); //SET PIN 0-3 AS INPUT
LPC_GPIO0->FIODIR |= ~(1<<4);  //SET PIN 4 AS INPUT

LPC_PINCON->PINMODE0 |= (3<<8); //enable pull down resistor in P0.4

}
