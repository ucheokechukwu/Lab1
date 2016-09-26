/* 
 * File:   newmain.c
 * Author: Uche
 *
 * Created on September 24, 2016, 3:32 AM
 */

#include <xc.h>
#include <pic.h>
#include <pic16f18857.h>
#include <time.h>

/*delay function - not working yet... 
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
*/

//initialize ADC
void adc_init()
{
    /*select I/O pins
     */
    TRISA = 0x04; //set RA2 to read/input pin
    TRISB = 0x00; //set all RB pins to write/output pins
    /*set A/D control registers
     */

    ADCON0 = 0x21; //turn ON ADC, clock from FOSC; left-justified ADRES
    ADCLK = 0x0F; // ADC conversion clock set at FOSC/32
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
       
    /*
     delay(1000); //delay for 100micro-seconds
     */
    
    ADCON0bits.ADGO=1; //set the GO bit to start the ADC conversion
    while (ADCON0bits.ADGO==1) continue; //wait for the conversion to end
    
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
    unsigned int LightSetPoint;
    LightSetPoint = 512; //half of the span of the span (1024)
    unsigned int AmbientLight;
    adc_init();
    while(1)
    {
        AmbientLight = adc_read();
        /*do the comparator
        * if the Ambient light is bright
        * reset RB5 (LED port pin)
        * ELSE set RB5 (LED port pin)
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
