/*
 * File:   SPI.c
 * Author: Faitoury
 *
 * Created on 29 MAY. 2020, 03:33 Pm
 */

#include "SPI.h"
#include "DIO.h"
#include <xc.h>
#include <avr/interrupt.h>

void SPI_Init(int Mode, int Presc1, int Presc2, int SPI_interrupt ) {
    /* Enable SPI , Choose master or slave , choose pre-scaler from datasheet default 1,1
     * Enable SPI_interrupt*/
    switch (Mode){
        case master :
          PINBas(SS,OUT);
          PINBas(MOSI,OUT);
          PINBas(SCK, OUT);
          SPCR |= (1<<SPE)|(1<<MSTR)|(Presc1<<SPR1)|(Presc2<<SPR0)|(SPI_interrupt<<SPIE); // Master Case
          break;
        case slave :
            PINBas(MISO,OUT);   
            SPCR |= (1<<SPE)|(Presc1<<SPR1)|(Presc2<<SPR0)|(SPI_interrupt<<SPIE); //Slave Case
        default :
            SPCR |= (1<<SPE)|(1<<SPR1)|(1<<SPR0)|(0<<SPIE);  
    }
}

void SPI_Write(char data){
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
}

void SPI_Master_init() {
    // Data Direction Configuration
    DDRB |= (1 << SS) | (1 << MOSI) | (1 << SCK);
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0); // | (1 << SPIE);
}