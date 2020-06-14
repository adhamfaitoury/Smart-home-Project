/*
 * File:   Bluetooth_USART.c
 * Author: Faitoury
 *
 * Created on MAY 27, 2020, 9:54 PM
 */

#include "DIO.h"
#include "Bluetooth_USART.h"
#include <util/delay.h>
#include <avr/io.h>
#include<stdio.h>
#include<math.h>

void USART_init(int recieve, int transmit, int rec_interrupt, int empty_Interrupt,
        int Mode,int parity1, int parity2, int speed) {
    //Start of USART initialization
    UCSRA |= (speed << U2X);
    UCSRB |= (transmit << TXEN) | (recieve << RXEN) | (rec_interrupt << RXCIE) | (empty_Interrupt << UDRIE);
    UCSRC |= (1<<URSEL)|(parity1<<UCSZ0) | (parity2<<UCSZ0);
    switch (Mode) {
        case Asynch:
            ;
            break;
        case Synch:
            UCSRC |= (1 << UMSEL)|(1<<URSEL);
            break;
        default:
           UCSRC |= (0 << UMSEL)|(1<<URSEL);
           break;
    }
    switch (speed) {
        case OFF:
            UBRRL = BAUD_PRESCALE;
            break;
        case ON:
            UBRRL = SPEED_BAUD_PRESCALE;
            break;
        default:
            UBRRL = BAUD_PRESCALE;
    }

}

void USART_transmitChar(char data) {
    while (!(UCSRA & (1 << UDRE)));
    UDR = data;
}

void USART_transmitString(char *data) {
    for (int i = 0; data[i] != '\0'; i++) {
        USART_transmitChar(data[i]);
    }

}

void newline() {
    char data[] = "\t\r";
    USART_transmitString(data);

}