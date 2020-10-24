#include <msp430g2553.h>
#include "mylcd.h"

#define DR P1OUT = P1OUT | BIT4             // define RS high
#define CWR P1OUT = P1OUT & (~BIT4)         // define RS low
#define READ P1OUT = P1OUT | BIT5           // define Read signal R/W = 1 for reading
#define WRITE P1OUT = P1OUT & (~BIT5)       // define Write signal R/W = 0 for writing
#define ENABLE_HIGH P1OUT = P1OUT | BIT6    // define Enable high signal
#define ENABLE_LOW P1OUT = P1OUT & (~BIT6)  // define Enable Low signal

unsigned int a;
unsigned int b;

void delay(unsigned int c)
{
    for (b = 0 ; b < c ; b++)
    {
        for (a = 0 ; a < 10 ; a++)
    }
}

void data_write(void)
{
    ENABLE_HIGH;
    delay(2);
    ENABLE_LOW;
}

void data_read(void)
{
    ENABLE_LOW; 
    delay(2); 
    ENABLE_HIGH; 
}

void check_busy(void)
{
    P1DIR &= ~(BIT3);               // make P1.3 as input
    while ((P1IN & BIT3) == 1)
    {
        data_read()
    }
    P1DIR |= BIT3;                  // make P1.3 as output
}

void send_command(unsigned char comd)
{
    check_busy();
    WRITE;
    CWR;
    P1OUT = (P1OUT & 0xF0) | ((comd >> 4) & 0x0F);   // send higher nibble
    data_write();                                   // give enable trigger
    P1OUT = (P1OUT & 0xF0) | (comd & 0x0F);         // send lower nibble
    data_write();                                   // give enable trigger
}

void send_data(unsigned char data)
{
    check_busy();
    WRITE;
    DR;
    P1OUT = (P1OUT & 0xF0) | ((data >> 4) & 0x0F); // send higher nibble
    data_write();                                  // give enable trigger
    P1OUT = (P1OUT & 0xF0) | (data & 0x0F);        // send lower nibble
    data_write();                                  // give enable trigger
}

void send_string(char *s)
{
    while (*s)
    {
        send_data(*s);
        s++;
    }
}

void lcd_init(void)
{
    P1DIR |= 0xFF;
    P1OUT &= 0x00;
    send_command(0x33);
    send_command(0x32);
    send_command(0x28);     // 4 bit mode
    send_command(0x0E);     // clear the screen
    send_command(0x01);     // display on cursor on
    send_command(0x06);     // increment cursor
    send_command(0x80);     // row 1 column 1
}