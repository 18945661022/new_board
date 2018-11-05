#include "REG51.H"
#include "INTRINS.H"


/**************************************
LCD 1602	����P0�ڣ�ʹ��P2��
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
//void LcdShowArray(unsigned char* ArrayPtr,unsigned char Num,unsigned char Line,unsigned char Location);	  //�������� �����ַ�����ȣ���ʾ�У��ڶ��ٸ�����0��ʼ�ƣ�
