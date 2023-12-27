#include p18f45k22.inc
config FOSC = HSHP

var1 equ 0x20

RST code 0x0
  goto Start

PGM code 
Start 
  ; es configuren els ports
  movlw B '00000001'
  movlb 0xF; BSR => SFR
  clrf PORTB, 0; CLEAR IN
  clrf LATB, 0; CLEAR OUT
  ; ports a digital
  movlw 0xF8
  movwf ANSELB, 1 

  movlw 0xF9
  movwf TRISB, 0; posa els pins que hi ha a w (11111001) a output

Loop

  btsfc PORTB, 0;
  goto cas1;
  bcf LATB


cas1 
  bsf LATB, 1; crec que ha escrit

delay_40cicles
 ;no sha de fer a la previa, 

  goto Loop
