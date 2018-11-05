#include "INTRINS.H"
#include "Delay_Fun.h"

/**************************************
stc12c5as60��ʱX΢��
���ֵ��
	n       us
	2		6
	3		8
	40		60
	45		70
	69      100
    165		240
**************************************/
void DelayXus(unsigned char n)
{
    while (n--)
    {
        _nop_();
        _nop_();
    }
}

/**************************************
stc12c5as60��ʱ1ms
**************************************/
void Delay1ms()
{
	unsigned char i;
	for(i=0;i<=9;i++)
	{
		DelayXus(69);	
	}		
}

/*************************************
stc12c5as60��ʱԼN ms
*************************************/
void Delayms(unsigned int Num)
{
	unsigned int i;
	for(i=0;i<Num;i++)
	{
		Delay1ms();
	}	
}
