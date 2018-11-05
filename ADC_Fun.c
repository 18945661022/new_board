#include "ADC_Fun.h"
#include "Delay_Fun.h"
#include "intrins.h"
#include "Stc_Math.h"

/*----------------------------
Initial ADC sfr
----------------------------*/
void InitADC(unsigned char Port)
{
    unsigned int i;
    P1ASF = Port;                          //Open 8 channels ADC function
    ADC_RES = 0;                           //Clear previous result
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    for(i=0;i<16;i++)                      //ADC power-on and delay   16ms
	{
		Delay1ms();
	}
}

/*----------------------------
Get ADC result
----------------------------*/
unsigned char GetADCResult(unsigned char ch)
{
    unsigned char I;
	//I = ADC_CONTR;
	
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL| ch | ADC_START;	//ADC_POWER | ADC_SPEEDLL |
    _nop_();                        //Must wait before inquiry
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//Wait complete flag
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC

	
	I = ADC_RES;

	ADC_RES = 0;
    return I;                 //Return ADC result
}

/*----------------------------
Get Vin(1000倍) 8位  精确小数后3位
----------------------------*/
unsigned int Vin_8(unsigned char ADCResult,unsigned int VREF)
{
	unsigned long Vin;
	EA = 0;                           
	//公式：Vin = Vcc(5)*ADCResult/256
	Vin = ((unsigned long)ADCResult*VREF*10)>>8;	
	EA = 1;
	return (unsigned int)Vin;	
}

/*----------------------------------------
Get Vin(1000倍) 8位  精确小数后3位  字符串
----------------------------------------
void GetVinString(unsigned char ADCResult,unsigned char* VinString)
{
	unsigned int Vin;
	unsigned char i;
	Vin = Vin_8(ADCResult,VREF);
	EA = 0;
	WordToStr(Vin,VinString,4);
	EA = 1;
    for(i=4;i>=2;i--)
	{
		VinString[i] = VinString[i-1];
	}
	VinString[1] = '.';
}
*/


