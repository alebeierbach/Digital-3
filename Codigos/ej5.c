/* Escribir un programa en C que permita realizar un promedio movil con los últimos
 * 8 datos ingresados por el puerto 1. Considerar que cada dato es un entero signado
 * y está formado por los 16 bits menos significativos de dicho puerto. El resultado,
 * también de 16 bits, debe ser sacado por los pines P0.0 al P0.11 y P0.15 al P0.18.
 * Recordar que en un promedio movil primero se descarta el dato mas viejo de los 8
 * datos guardados, se ingresa un nuevo dato proveniente del puerto y se realiza la
 * nueva operación de promedio con esos 8 datos disponibles, así sucesivamente.
 * Considerar el uso de un retardo antes de tomar una nueva muestra por el puerto.
 */



#include "LPC17xx.h"


void delay(int tiempo){
    for(int i=0; i<tiempo; i++){}   //delay
}		

void promedio(){
    int suma=0;
    for(int i=0;i<8;i++){
        suma+= M[i];
    }
promedio=suma/8;
}

int main(void) {

    uint16_t M[8]=0;
    uint16_t promedio=0;
    uint16_t dato;
    int rep=0;

LPC_PINCON->PINSEL0 &= ~(0xFFFFFF);  //habilito GPIO de PIN 0 a 11
LPC_PINCON->PINSEL1 &= ~(0b111111);  //habilito GPIO de PIN 15 a 18
LPC_PINCON->PINSEL1 &= ~(0b11);  //habilito GPIO1 de PIN 0

LPC_GPIO1->FIODIR0 |= ~(1); //activo como entrada los pines P1.0
LPC_GPIO0->FIODIR0 |= (0xFF); //activo como salida los pines P0.0 hasta P0.7
LPC_GPIO0->FIODIR1 |= (0x8F); //activo como salida los pines P0.8 hasta P0.11 y P0.15
LPC_GPIO0->FIODIR2 |= (0x07); //activo como salida los pines P0.16 hasta P0.18

LPC_PINCON->PINMODE2 |= (0b11); //le pongo una resistencia de pull down a la entrada de P1.0

while(1){
dato = (LPC_GPIO1->FIOPIN & (0xFFFF));

for(rep; rep<8; i++){
    M[i]=dato;
    promedio();
}
if(rep==8){
    rep=0;
}

aux1=promedio & (0xFFF); //primeros 12 bits para mostrar del 0 al 11
aux2=promedio & (0xF<<12) //los otros 4 bits para mostrar del 15 al 18

LPC_GPIO0->FIOSET |= (aux1 | (aux2<<15)); //saco por los bits correspondientes el valor del promedio


}
}
