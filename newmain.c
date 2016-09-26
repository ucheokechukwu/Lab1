/* 
 * File:   newmain.c
 * Author: Uche
 *
 * Created on September 26, 2016, 6:32 AM
 */

#include <xc.h>
#include <pic.h>
#include <pic16f18857.h>

//initialize ADC
void adc_init()
{
    //select I/O pins//
    TRISA2 = 1; //set RA2 to read/input pin
    TRISB5 = 0; //set RB5 to write/output pin
    //set A/D control registers//
    ADCON0 = 0x01; //turn ON ADC, clock from FOSC
    ADCLK = 0xF0; //FOSC/32
    ADREF = 0x00; // Vref (+) and (-) are Vdd & Vss
    ADPCH = 0x04; // Select Analog channel A2
     
} 

//read ADC value
void adc_read()
{
    //configure the interrupt if required
    //delay
    int AmbientHigh;
    AmbientHigh = 0;
    ADCON0bits.ADGO=1; //set the GO bit to start the ADC conversion
    while (ADCON0bits.ADGO=1) continue;
    
    //read the value
    /*do the comparator
     * if the Ambient light is bright
     * turn off the LED output RB5
     * if Ambient is dim, turn on the LED output RB5.
    */
    if (AmbientHigh = 1)
    {
        PORTBbits.RB5 = 0; //  set RB5 (LED port pin) OFF
        }
    else 
    {
        PORTBbits.RB5 = 1; // set RB5 (LED port pin) ON)
        } 
        
        return;
    
} 
 
// Main program
void main (void)
{
    adc_init();
    while(1)
    {
        adc_read();
    }
}