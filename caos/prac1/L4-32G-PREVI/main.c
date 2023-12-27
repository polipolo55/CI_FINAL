// A proposal for your code... Just to inspire you
#include <xc.h>
#define _XTAL_FREQ 8000000
#include "config.h"
#define PINA0 PORTAbits.RA0
#define PINB0 PORTBbits.RB0
#define LED PORTDbits.RD5 // Per indicar que hem connectat un LED aquí al bit 5 del Port D
#define APAGA 0
#define ENCEN 1
void configPIC(){
//config PIC
ANSELA=0x00; // All pins as digital
ANSELB=0x00; // All pins as digital
TRISA=0x00;
TRISB=0x01;
}

void main(void){
configPIC();
int a = APAGA;
while(1) {
   /*if(PINB0 == 1){ //esta pulsado
      PINA0 = ENCEN;
      } else{
	    PINA0 = 0;
	 } PROGRAMA 1*/
   
   if(PINB0 == 1){    
      PINA0 = !PINA0;
      __delay_ms(200);
   }
   
     
}
}