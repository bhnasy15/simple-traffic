#ifndef registers_h
#define registers_h

#define address volatile unsigned char*

/**************************************************/
				//G.I.O
/**************************************************/
#define PORTA *((address) 0x3B)
#define DDRA  *((address) 0x3A)
#define PINA  *((address) 0x39)

#define PORTB *((address) 0x38)
#define DDRB  *((address) 0x37)
#define PINB  *((address) 0x36)

#define PORTC *((address) 0x35)
#define DDRC  *((address) 0x34)
#define PINC  *((address) 0x33)

#define PORTD *((address) 0x32)
#define DDRD  *((address) 0x31)
#define PIND  *((address) 0x30)
/**************************************************/


/**************************************************/
				//TIMERS
/**************************************************/
#define TIMSK *((address) 0x59)
#define TIFR *((address) 0x58)

#define TCCR0 *((address) 0x53)
#define TCNT0 *((address) 0x52)
/**************************************************/


#endif
