#include "reg51.h"

/**************************************
am2305����			  
**************************************/
sbit Sensor_SDA = P1^1;                     //AM2305�����ݿ�λP1.1	 p1.6 p1.7Ҳ��
unsigned char AM2305_Start(unsigned char delay);
unsigned char AM2305_ReadByte();