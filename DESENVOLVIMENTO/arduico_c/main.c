/*
 */

#include <avr/io.h>  //location of ports and pins
#include <util/delay.h>  //delay features

int main(void)
{
    /* set pin 5 of PORTB for output*/
    DDRB |= _BV(DDB5);

    //data direction register for port B

    while(1){

    /* set pin 5 high to turn led on */

    PORTB |= _BV(PORTB5);  //pin 13

    _delay_ms(1000); //delay 1 second

    /*set pin 5 to turn led off */
    PORTB &= ~_BV(PORTB5);  //BV: bit value
    _delay_ms(1000);
    }


    return 0;
}
