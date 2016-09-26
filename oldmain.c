/* 
 * File:   newmain.c
 * Author: Uche
 *
 * Created on September 24, 2016, 3:32 AM
 */

#include <xc.h>
#include <pic.h>
#include <pic16f18857.h>

//initialize ADC
void adc_init()
{
    /*select I/O pins
     */
    TRISA2 = 1; //set RA2 to read/input pin
    TRISB5 = 0; //set RB5 to write/output pin
    /*set A/D control registers
     */
    
    ADCON0 = 0x21; //turn ON ADC, clock from FOSC; left-justified ADRES
    ADCLK = 0x0F; //FOSC/32
    ADREF = 0x00; // Vref (+) and (-) are Vdd & Vss
    ADPCH = 0x02; // Select Analog channel A2
     
} 

//read ADC value
void adc_read()
{
    /*
     AmbientLight is the value from the ADC result
     LightSetPoint is the set point of ambient light 
    */
       
    unsigned int LightSetPoint; 
    unsigned int AmbientLight;
       
    LightSetPoint = 512; //half of the span of the span (1024)
       
    //delay - wait for the acquisition time
    
    ADCON0bits.ADGO=1; //set the GO bit to start the ADC conversion
    while (ADCON0bits.ADGO=1) continue; //wait for the conversion to end
    
    
    //read ADC result & save as AmbientLight
    AmbientLight = ADRESL;
    AmbientLight += ADRESH << 8; //left-justified ADRES

    

    /*do the comparator
     * if the Ambient light is bright
     * set RB5 (LED port pin) OFF
     * ELSE set RB5 (LED port pin) ON
    */
    if (AmbientLight > LightSetPoint) 
    {
        PORTBbits.RB5 = 0; 
        }
    else 
    {
        PORTBbits.RB5 = 1; 
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
