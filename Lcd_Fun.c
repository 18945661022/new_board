/**************************************
12c5a60s2	11.0592MHZ
**************************************/
#include "Lcd_Fun.h"
#include "Delay_Fun.h"
							   
/**************************************
检测1602忙闲
**************************************/
bit LcdBusy()
{
bit result;
P0 = 0x80;
lcdrs = 0;
lcdrw = 1;
lcden = 1;
_nop_();
_nop_();
_nop_();
_nop_();
result = (bit)(P0 & 0x80);
lcden = 0;
return result;
}

void RDBF(void)
{
	unsigned char temp;
	P0=0xFF; //数据线为输入
	lcdrs=0; // RS=0
	lcdrw=1; // RW=1
	//DelayXus(2);
	while(1)
	{	
	lcden=1;
	//DelayXus(3);
	temp=P0;
	lcden=0; // E=0
	if ((temp&0x01)==0) break;
	//DelayXus(3);
	}
}

/**************************************
写1602命令
**************************************/
void LcdWriteCmd(unsigned char CMD)
{
/** /
	//while(LcdBusy());
	RDBF();
	test_led = 0;
	_nop_();
	lcdrs = 0;
	lcdrw = 0;
	lcden = 0;
//	_nop_();
//	_nop_();
	P0 = CMD;
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
	lcden = 1;
//	DelayXus(370);
	lcden = 0;
	DelayXus(370);
/**/
	RDBF();
	
	lcdrs=0;
	lcdrw=0;
	P0=reverse8(CMD);
	lcden=1;
	lcden=0;
//	DelayXus(370);
	/**/
}

/**************************************
写1602数据
**************************************/
void LcdWriteDat(unsigned char Dat)
{
/**/
	//while(LcdBusy());
	RDBF();
	lcdrs = 1;
	lcdrw = 0;
	lcden = 0;
	//_nop_();
	//_nop_();
	P0 = reverse8(Dat);
	//_nop_();
	//_nop_();
	//_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
	lcden = 1;
//	DelayXus(370);
	lcden = 0;
	//DelayXus(370);
	/** /
	RDBF();
	lcdrs=1;
	lcdrw=0;
	lcden = 0;
	P0=Dat;
	lcden=1;
	lcden=0;
	//DelayXus(370);
	/**/
}														

/**************************************
1602初始化
**************************************/
void LcdInit()
{
    DelayXus(1500);
	LcdWriteCmd(0x38);
	DelayXus(5000);
	LcdWriteCmd(0x38);
	DelayXus(5000);
	LcdWriteCmd(0x38);
	//LcdWriteCmd(0x08);
    //LcdWriteCmd(0x01);
	LcdWriteCmd(0x0c); 
	LcdWriteCmd(0x06);
	//DelayXus(1000);
	//LcdWriteCmd(0x38);
	//LcdWriteCmd(0x06);
		//DelayXus(1000);

	//LcdWriteCmd(0x0c);  	

		//DelayXus(1000);
}

void LcdInit1()
{
	//test_led = 1;
	//test_led = 0;
	//test_led = 1;		
//	Delayms(1000);
	DelayXus(1500);
	LcdWriteCmd(0x30);

	DelayXus(500);
	LcdWriteCmd(0x30);
	DelayXus(500);
	LcdWriteCmd(0x0C);
	//LcdWriteCmd(0x08);
	DelayXus(500);
    LcdWriteCmd(0x01);
		Delayms(12);
	//DelayXus(5000);
	//LcdWriteCmd(0x0c); 
	//DelayXus(5000);
	LcdWriteCmd(0x06);
		

}

//字节（8位）翻转
unsigned char reverse8( unsigned char c )
{
     c = ( c & 0x55 ) << 1 | ( c & 0xAA ) >> 1;
     c = ( c & 0x33 ) << 2 | ( c & 0xCC ) >> 2;
     c = ( c & 0x0F ) << 4 | ( c & 0xF0 ) >> 4;
     return c;
}

/*
void LcdReInit()
{
	LcdWriteCmd(0x38);
	LcdWriteCmd(0x0c); 
	LcdWriteCmd(0x06);	
}

void lcdClean()
{
	LcdWriteCmd(0x01);
}
*/
/**************************************
显示字符数组
*************************************
void LcdShowArray(unsigned char* ArrayPtr,unsigned char Num,unsigned char Line,unsigned char Location)
{
	unsigned char i,Addr;
	if(Location + Num >= 17)
	{
		return;
	}
	if(Line == 1)
	{
		 Addr = Location + 0x80;
	}
	if(Line == 2)
	{
		 Addr = Location + 0xC0;
	}
	LcdWriteCmd(Addr);
	for(i=0;i<Num;i++)
	{
		if(ArrayPtr[i] != 0x00)
		{
			LcdWriteDat(ArrayPtr[i]);
			Location++;
		}
	}
	for(i=0;i<(16-Location);i++)
	{
		LcdWriteDat(' ');
	}
}
*/