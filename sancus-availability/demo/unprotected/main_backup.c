#include <sancus/sm_support.h>
#include <msp430f1121.h>
#include <stdio.h>
#include <sancus_support/uart.h>
#include <sancus/reactive_stubs_support.h>
#include "sm_io_wrap.h"
#include <sancus_support/tsc.h>


#define LED1 *(volatile uint8_t*) 0x0090 
#define LED2 *(volatile uint8_t*) 0x0091
#define LED3 *(volatile uint8_t*) 0x0092
#define LED4 *(volatile uint8_t*) 0x0093
#define LED5 *(volatile uint8_t*) 0x0094
#define LED6 *(volatile uint8_t*) 0x0095
#define LED7 *(volatile uint8_t*) 0x0096
#define LED8 *(volatile uint8_t*) 0x0097


void led_init(void)
{
    LED1 = 0x71; // 'F'
    LED2 = 0x79; // 'E'
    LED3 = 0x79; // 'E'
    LED4 = 0x7c; // 'b'
    LED5 = 0x5e; // 'd'
    LED6 = 0x77; // 'A'
    LED7 = 0x79; // 'E'
    LED8 = 0x5E; // 'd'
    TACCTL0 = CCIE;
    TACTL = TASSEL_2 + MC_1 + ID_3;
    TACCR0 = 62500; 

    P1DIR = 0;
    P1SEL = 0;
    P1IE = 1;
    P1IES = 0;

}



void cycle_leds(void)
{
    uint8_t foo = LED1;
    LED1 = LED2;
    LED2 = LED3;
    LED3 = LED4;
    LED4 = LED5;
    LED5 = LED6;
    LED6 = LED7;
    LED7 = LED8;
    LED8 = foo;
}

int timerCount = 0;
void __attribute__((__interrupt__ (TIMERA0_VECTOR))) Timer_A0(void)
{
    timerCount = (timerCount+1)%40;
    if (timerCount == 0)
    {
        cycle_leds();
    }
}

void __attribute__((__interrupt__ (0x0004))) Attacker(void)
{
    LED1 = 0x77; // 'A'
    LED2 = 0x76; // 'H'
    LED3 = 0x77; // 'A'
    LED4 = 0x76; // 'H'
    LED5 = 0x77; // 'A'
    LED6 = 0x76; // 'H'
    LED7 = 0x77; // 'A'
    LED8 = 0x76; // 'H'
    while(1);
}


int main()
{
    WDTCTL = WDTPW + WDTHOLD;
    uart_init();
    led_init();  
    asm("eint");
    
    while(1)
    {
      if ((P1IN & 1) == 1) //BTN1
      {
      LED1 = 0x77; // 'A'
      LED2 = 0x76; // 'H'
      LED3 = 0x77; // 'A'
      LED4 = 0x76; // 'H'
      LED5 = 0x77; // 'A'
      LED6 = 0x76; // 'H'
      LED7 = 0x77; // 'A'
      LED8 = 0x76; // 'H'
      asm("dint");
      }
    }
}




