/* 
 * File:   newmain.c
 * Author: Uche
 *
 * Created on September 24, 2016, 3:32 AM
 */

#include <xc.h>
#include <pic.h>
#include <pic16f18857.h>

unsigned int LightSetPoint;// LightSetPoint is the set point of ambient light 
unsigned int AmbientLight;//AmbientLight is the value from the ADC result
unsigned int i;

/*---initialize ADC---*/
void adc_init()
{
    /* select I/O pins */
    TRISA = 0x04; //set RA2 to read/input pin
    TRISB = 0x00; //set all RB pins to write/output pins
    
    /* set A/D control registers */
    ADCON0 = 0x21; //turn ON ADC, clock from FOSC; right-justified ADRES
    ADCLK = 0x0F; // ADC conversion clock set at FOSC/32
    ADREF = 0x00; // Vref (+) and (-) are Vdd & Vss
    ADPCH = 0x02; // Select Analog channel A2
     
} 

/*--read ADC value--*/
unsigned int adc_read()
{
/*---AmbientLight is the value from the ADC result---*/
       
    ADCON0bits.ADGO=1; //set the ADGO bit to start the ADC conversion
    while (ADCON0bits.ADGO);// continue; //wait for the conversion to the end
    
    /*---read ADC result & save as AmbientLight---*/
    AmbientLight = ADRESL;
    AmbientLight += ADRESH << 8; //right-justified ADRES
    
    return AmbientLight;
    
} 
 
// Main program
void main (void)
{
    for (i=0; i<1500; i--); 
    adc_init();
    LightSetPoint = 512;//half of the span (1024)
    
    /* Do the comparator:
     * IF the Ambient light is bright
     *       set RB5 (LED port pin) OFF
     * ELSE  set RB5 (LED port pin) ON
     */
    while(1)
    {
        AmbientLight = adc_read();
        
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

