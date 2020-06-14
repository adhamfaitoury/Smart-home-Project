/* 
 * File:   main.c
 * Author: Faitoury
 *
 * Created on May 29, 2020, 3:59 PM
 */

#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include "DIO.h"
#include <stdio.h>
#include "Bluetooth_USART.h"
#include "SPI.h"

char str0[] = "Enter O/o to Open & C/c to Close LED 1 \t\rEnter W/w to Open & S/s  to Close LED 2";
char str1[] = "LED 1 enter O to Open or C to Close";
char str11[] = "  LED1 is ON";
char str12[] = "  LED1 is OFF";
char str2[] = "LED 2 enter O to Open or C to Close";
char str21[] = "  LED2 is ON";
char str22[] = "  LED2 is OFF";
char str3[] = "Enter O or o to Open LED & C or c to Close LED ";
char Rec;
int led = 1;

ISR(USART_RXC_vect) {
    Rec = UDR;
    if ((Rec == 'O') || (Rec == 'o')) {              //check character send 
        USART_transmitString(str11);                 //tranmit status of LED 2 as ON 
        newline();
    } else if ((Rec == 'C') || (Rec == 'c')) {       //check character send
        USART_transmitString(str12);                 //tranmit status of LED 2 as OFF
        newline();
    }
    else if ((Rec == 'W') || (Rec == 'w')) {         //check character send
        USART_transmitString(str21);                 //tranmit status of LED 1 as ON
        newline();
    }
    else if ((Rec == 'S') || (Rec == 's')) {         //check character send
        USART_transmitString(str22);                 //tranmit status of LED 1 as OFF
        newline();
    }
}


int main(void) {
    // Configure the pins of master
    PINCas(LED2, OUT);

    // Bluetooth transmit
    /* Enter ON/OFF for following parameters receive , transmit, receive interrupt
     * empty_Interrupt,Synchronous or Asynchronous for mode ,parity1,parity2,speed
     */


    USART_init(ON, ON, ON, OFF, Asynch, ON, ON, OFF); // USART initialize
    SPI_Init(master, 1, 1, OFF); // SPI Master initialize with prescaler 128 with no Interrupt 
    USART_transmitString(str0); // instruction message for operation
    newline();
    sei();
    while (1) {
        // sending characters to slave controller
        SPI_Write(Rec);
        _delay_ms(100);

    }
}





