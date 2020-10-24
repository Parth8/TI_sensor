#include <msp430g2553.h>
#include <stdlib.h>
#include <string.h>
#include "mylcd.h"

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // stop watchdog timer

    while(1)
    {
        lcd_init();
        send_string("The temperature value is: ");
        send_command(0xC0);
        send_string("24");
        __delay_cycles(7000000000000);
    }
}