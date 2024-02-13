;
; Matriz.asm
;
; Created: 31/10/2021 01:18:26 p. m.
; Author : La_de
;


; Replace with your application code

	.def xd=r16
	.def xd2=r17

	.cseg
	.org 0
	ldi xd, $ff
	out portd, xd
	ldi xd, $ff
	out ddrd, xd
	
	ldi xd, $00
	out portc, xd
	ldi xd, $ff
	out ddrc, xd
	
	ldi xd, $00
	out portb, xd
	ldi xd, $ff
	out ddrb, xd

main:	rjmp L
;		ldi xd, $ff
;		out portd, xd
;		ldi xd, $00
;		out portc, xd
;		ldi xd, $00
;		out portb, xd
		rjmp main



L:		ldi xd, $0f		////////////////////////////////////////
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $ff
		out portd, xd

		ldi xd, $0d
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $ff
		out portd, xd
		
		ldi xd, $0b
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $ff
		out portd, xd 

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $07 
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $c0
		out portd, xd 
		
/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0f 
		out portc, xd
		ldi xd, $0e
		out portb, xd
		ldi xd, $c0
		out portd, xd		 

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0f 
		out portc, xd
		ldi xd, $0d
		out portb, xd
		ldi xd, $c0
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		rjmp main

A:		ldi xd, $0f		/////////////////////////////////////
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $ff
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0d
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $fc
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0b
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $fe
		out portd, xd 	

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $07
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $33
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0f
		out portc, xd
		ldi xd, $0e
		out portb, xd
		ldi xd, $33
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0f
		out portc, xd
		ldi xd, $0d
		out portb, xd
		ldi xd, $fe
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0f
		out portc, xd
		ldi xd, $0b
		out portb, xd
		ldi xd, $fc
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd


		rjmp main

P:		ldi xd, $0f		/////////////////////////////////////
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $ff
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0d
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $ff
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0b
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $ff
		out portd, xd 	

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $07
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $1b
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0f
		out portc, xd
		ldi xd, $0e
		out portb, xd
		ldi xd, $1b
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0f
		out portc, xd
		ldi xd, $0d
		out portb, xd
		ldi xd, $1f
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0f
		out portc, xd
		ldi xd, $0b
		out portb, xd
		ldi xd, $0e
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		rjmp main

R:		ldi xd, $0e		/////////////////////////////////////
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $00
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0d
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $ff
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0b
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $ff
		out portd, xd 	

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $07
		out portc, xd
		ldi xd, $0f
		out portb, xd
		ldi xd, $1b
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0f
		out portc, xd
		ldi xd, $0e
		out portb, xd
		ldi xd, $1b
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0f
		out portc, xd
		ldi xd, $0d
		out portb, xd
		ldi xd, $ff
		out portd, xd

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd

		ldi xd, $0f
		out portc, xd
		ldi xd, $0b
		out portb, xd
		ldi xd, $ee
		out portd, xd  

/*Separador	*/	ldi xd, $00
/*			*/	out portd, xd


		rjmp main