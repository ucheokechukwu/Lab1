/* 
 * File:   altmain.c
 * Author: Uche
 * Description: alternative code; better coding 'ethics'
 * Created on September 26, 2016, 10:32 AM
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
    ADCLK = 0xF0; //FOSC/32
    ADREF = 0x00; // Vref (+) and (-) are Vdd & Vss
    ADPCH = 0x02; // Select Analog channel A2
     
} 

//read ADC value
unsigned int adc_read()
{
    /*
     AmbientLight is the value from the ADC result
    */
    unsigned int AmbientLight;
       
    //delay - wait for the acquisition time.
    
    ADCON0bits.ADGO=1; //set the GO bit to start the ADC conversion
    while (ADCON0bits.ADGO=1) continue; //wait for the conversion to end
    
    //read ADC result & save as AmbientLight
    AmbientLight = ADRESL;
    AmbientLight += ADRESH << 8; //left-justified ADRES
    
    return AmbientLight;
    
} 
 
// Main program
void main (void)
{
     /*
     AmbientLight is the value from the ADC result
     LightSetPoint is the set point of ambient light 
    */
    adc_init();
    while(1)
    {
        unsigned int LightSetPoint;
        LightSetPoint = 512; //half of the span of the span (1024)
        unsigned int AmbientLight = adc_read();
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
    }
}
