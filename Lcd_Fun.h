#include "REG51.H"
#include "INTRINS.H"


/**************************************
LCD 1602	数据P0口，使能P2口
**************************************/
sbit lcdrs = P2^5;				   //rs
sbit lcdrw = P2^6;				   //r/w
sbit lcden = P2^7;				   //en



sfr P2M1 = 0x95;
sfr P2M0 = 0x96;

bit LcdBusy();
void LcdWriteCmd(unsigned char CMD);
void LcdWriteDat(unsigned char Dat);
void LcdInit();
void LcdInit1();
unsigned char reverse8( unsigned char c );
//void LcdClean();
//void LcdReInit();
//void LcdShowArray(unsigned char* ArrayPtr,unsigned char Num,unsigned char Line,unsigned char Location);	  //参数依次 数组地址，长度，显示行，第多少个（从0开始计）
