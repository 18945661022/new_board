#include "reg51.h"

/**************************************
18b20����			  
**************************************/
sbit DQ = P1^0;                     //DS18B20�����ݿ�λP1.0

bit DS18B20_Reset();
void DS18B20_WriteByte(unsigned char dat);
unsigned char DS18B20_ReadByte();
unsigned char Get_Integer(unsigned char tph,unsigned char tpl);
unsigned int Get_Decimal(unsigned char tpl);
//void GetTempString(unsigned char TPH,unsigned char TPL,unsigned char* Array);
void  DS18B20_Init();