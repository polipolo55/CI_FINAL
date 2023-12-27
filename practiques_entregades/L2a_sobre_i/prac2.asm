#include p18f45k22.inc
config FOSC = HSHP

var1 equ 0x20
COUNT_Value EQU 0X03  ; number of times the loop is to be executed


COUNT EQU 0x01		; Define loop variable
RST code 0x0
  goto Start

PGM code 
Start 
  ; es configuren els ports
  movlw B'00000001'
  movlb 0xF; BSR => SFR
  clrf PORTB, 0; CLEAR IN
  clrf LATB, 0; CLEAR OUT
  ; ports a digital
  movlw 0xF8
  movwf ANSELB, 1 

  movlw 0xF9
  movwf TRISB, 0; posa els pins que hi ha a w (11111001) a output

Loop
  btfss PORTB, 0;
  goto cas1;
  bcf LATB, 1 , 0;
  goto cas2;
cas1 
	call delay_40cicles
  bsf LATB, 1; crec que ha escrit
	goto ending
cas2
	call delay_40cicles
  bsf LATB, 0; 
	goto ending
delay_40cicles
  movlw	COUNT_Value	
  movwf	COUNT
	nop

delay_loop
  decfsz	COUNT,1
	goto delay_loop
	return
ending
	goto Loop
END
