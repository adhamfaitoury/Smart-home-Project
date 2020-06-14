/*
 * File:   main.c
 * Author: Faitoury
 *
 * Created on 29 MAY 2020, 03:46 Pm
 */

#include <xc.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "DIO.h"
#include "Bluetooth_USART.h"
#include "SPI.h"

char str1[] = "LED is ON";
char str2[] = "LED is OFF";
char str0[] = "Enter O or o to Open LED & C or c to Close LED ";

ISR(SPI_STC_vect) {
            if ((SPDR == 'O') || (SPDR == 'o')) {      // Read Character send by Usart and Check it 
                 PORTC |= (1 << LED2);                 // If Character Send is O or o Led 2 is Opened
            } 
            else if ((SPDR == 'C') || (SPDR == 'c')) { // Read Character send by Usart and Check it 
                PORTC &= ~(1 << LED2);                 // If Character Send is C or c Led 2 is Closed
            } 
            else if ((SPDR == 'W') || (SPDR == 'w')) { // Read Character send by Usart and Check it 
                PORTC |= (1 << LED1);                  // If Character Send is W or w Led 1 is Opened
            }
            else if ((SPDR == 'S') || (SPDR == 's')) { // Read Character send by Usart and Check it
                PORTC &= ~(1 << LED1);                 // If Character Send is W or w Led 1 is closed
            }
    }

    int main(void) {
        PORTCas(OUT);                                // set data direction for PortC to be out
        SPI_Init(slave, 1, 1, ON);                   // initiate SPI  as Slave with Interrupt 
        sei();                                       // Enable SPI Interrupt
        while (1) {
        }
    }

    