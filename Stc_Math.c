#include "Stc_Math.h"
#include "reg51.h"

unsigned char Average(unsigned char* str)
{
	unsigned char i,Max,Min;
	unsigned int sum;
	Max = str[0];
	Min = str[0];
	for(i=0;i<=9;i++)
	{
		if(str[i] >= Max)
		{
			Max = str[i];
		}
		if(str[i] <= Min)
		{
			Min = str[i];
		} 
	}
	sum = 0;
	for(i=0;i<=9;i++)
	{
		sum = sum + (unsigned int)str[i];	
	}
	sum = sum - (unsigned int)Max - (unsigned int)Min;
	Max = (unsigned char)(sum>>3);
	return Max;
}

unsigned char Compare(unsigned int first,unsigned int second)
{
	unsigned char signal1,signal2;							 //0正数，1负数
	signal1 = 0;
	signal2 = 0;
	if(first == second)
	{
		return 0;
	}
	if(first&0x8000)
	{
		signal1 = 1;
	}
	if(second&0x8000)
	{
		signal2 = 1;
	}
	if(signal1==signal2)
	{
		if(signal1==0)
		{
			if(first>second)
			{
				return 1;
			}
			else  
			{
				return 2;
			}
		}
		else
		{
			if(first>second)
			{
				return 2;
			}
			else  
			{
				return 1;
			}
		}
	}
	if(signal1>signal2)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}


