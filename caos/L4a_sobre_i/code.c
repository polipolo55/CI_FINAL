/* Main.c 
 * Processor: PIC18F45K22
 * Compiler:  MPLAB XC8
 */

#include <xc.h>
#include <string.h>
#include "config.h"
#include "GLCD.h"
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 8000000  


int posx = 63/2;
int posy = 127/2;

int dirx = 0;
int diry = 0;

int speed = 1;

int PORTC_ANT;

const char * s1 = "ASTEROIDES\n";
const char * s2 = "--------\n";
const char * s3 = "Marc Ortega\n";
const char * s4 = "Pol Casanovas\n";

long long t1 = 0;

int detectEdge (int PORT_ant, int PORT_act, int pin, int edge)
{
    int mask = 1 << pin;

        if (edge == 1) 
        {
            if ((PORT_ant & mask) == 0 && (PORT_act & mask) != 0) return 1;
        }
        else
        {
            if ((PORT_ant & mask) != 0 && (PORT_act & mask) == 0) return 1;
        }

    return 0;
}

void tic(void) {

    putchGLCDreal(posx, posy, 133);
    posx += dirx * speed;
    posy += diry * speed;
    putchGLCDreal(posx, posy, 137);
    TMR0 = 0x0AD5;
    TMR0IF = 0;
    PORTC_ANT = PORTC;

}

void interrupt high_RSI(void)
{
   if(TMR0IF) 
   {
      tic();
   }
}





void writeTxt(byte page, byte y, char * s) {
   int i=0;
   while (*s!='\n' && *s!='\0') 
   {
      putchGLCD(page, y+i, *(s++));
      i++;
   };
}

void configPIC(void) { 

   ANSELA=0x00; 
   ANSELB=0x00;                  
   ANSELC=0x00;                  
   ANSELD=0x00;                  
   
   TRISD=0x00;		   
   TRISB=0x00;
   TRISC=0x0F;
    
   PORTD=0x00;
   PORTB=0x00;

   GIEH = 1;
   T0CONbits.T08BIT  = 0;
   T0CONbits.T0CS    = 0;
   T0CONbits.T0SE    = 1;
   T0CONbits.PSA     = 0;
   T0CONbits.T0PS2   = 0;
   T0CONbits.T0PS1   = 0;
   T0CONbits.T0PS0   = 1;
   TMR0H             = 0x3C;
   TMR0L             = 0xB0;
   INTCONbits.TMR0IF = 0;
   INTCONbits.T0IE   = 0;
   T0CONbits.TMR0ON  = 1;
   
   
}

void main(void)
{
   
   configPIC();
   

   int gameState = 0;
   

   
   
   GLCDinit();		   //Inicialitzem la pantalla
   clearGLCD(0,7,0,127);   //Esborrem pantalla
   setStartLine(0);        //Definim linia d'inici

   writeTxt(2, 8, s1);
   writeTxt(3, 9, s2);
   writeTxt(4, 7, s3);
   writeTxt(5, 7, s4);
   putchGLCD(posx, posy, 132);

   while (1)
   {   
      if(gameState == 0) {
	 ++t1;
	 __delay_ms(1);
	 if(PORTC != 0) {
	    clearGLCD(0,7,0,127);
	    srand(t1);
	    putchGLCD(rand()%7, rand()%24, 136);
	    putchGLCD(rand()%7, rand()%24, 137);
	    putchGLCD(rand()%7, rand()%24, 137);
	    putchGLCD(rand()%7, rand()%24, 136);
	    gameState = 1;  
	    INTCONbits.T0IE = 1;

	 }
      }
      else if(gameState == 1) {    
      
        if(detectEdge(PORTC_ANT,PORTC, 1, 1)) {
            diry = -1;
        }
        else if(detectEdge(PORTC_ANT,PORTC, 1, 0)) {
            diry = 0;
        }

        if(detectEdge(PORTC_ANT,PORTC, 3, 1)) {
            diry = 1;
        }
        else if(detectEdge(PORTC_ANT,PORTC, 3, 0)) {
            diry = 0;
        }

        if(detectEdge(PORTC_ANT,PORTC, 0, 1)) {
            dirx = -1;
        }
        else if(detectEdge(PORTC_ANT,PORTC, 0, 0)) {
            dirx = 0;
        }

        if(detectEdge(PORTC_ANT,PORTC, 2, 1)) {
            dirx = 1;
        }
        else if(detectEdge(PORTC_ANT,PORTC, 2, 0)) {
            dirx = 0;
        }
      }    
   }
}
