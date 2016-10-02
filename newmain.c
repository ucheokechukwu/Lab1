/* 
 * File: lab1_group2.c
 * Author: Group2
 * Code by: Uchechukwu Okechukwu	
 * Debugging by: Yue Wang, Stephen Cahill 
 * Created on September 24, 2016, 3:32 AM
 */

#include <xc.h>
#include <pic.h>
#include <pic16f18857.h>

/*---declare variables---*/

unsigned int LightSetPoint; // Set point of ambient light 
unsigned int AmbientLight; // Value from the ADC result
unsigned int i; //Counter for the delay for loop

/*---initialize ADC---*/
void adc_init()
{
    /* select I/O pins */
    TRISA1 = 1; //set RA1 to read/input pin
    TRISB5 = 0; //set RB5 to write/output pin
    
    /* set A/D control registers */
    ADCON0 = 0x84; //turn ON ADC, clock from FOSC, right-justified ADRES
    ADCLK = 0x0F; // ADC conversion clock set at FOSC/32
    ADREF = 0x00; /* Vref(+) and Vref (-) are selected from 
                     the Vdd and Vss  respectively*/
    ADPCH = 0x01; // Select Analog channel A1
     
} 

/*--read ADC value--*/
unsigned int adc_read()
{       
    ADCON0bits.ADGO=1; //set the ADGO bit to start the ADC conversion
    while (ADCON0bits.ADGO); //wait for the conversion to the end
    
    /*---read ADC result & save as AmbientLight---*/
    AmbientLight = ADRESL;
    AmbientLight += ADRESH << 8; //right-justified ADRES
    
    return;    
} 

void main (void)
{
    for (i=0; i<1500; i--); //delay loop for ADC acquisition time

    adc_init(); //initialize ADC//
    LightSetPoint = 512; //set to half of the span (1024)
    
    /* Do the comparator:
     * IF the Ambient light is bright
     *       set RB5 (LED port pin) OFF
     * ELSE  set RB5 (LED port pin) ON
     */
    while(1)
    {
        adc_read();
        
        if (AmbientLight < LightSetPoint) 
        {
            PORTBbits.RB5 = 0; 
        }
        else 
        {
            PORTBbits.RB5 = 1; 
        } 
    }
}
