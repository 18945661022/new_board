#include "reg51.h"

/**************************************
am2305配置			  
**************************************/
sbit Sensor_SDA = P1^1;                     //AM2305的数据口位P1.1	 p1.6 p1.7也可
unsigned char AM2305_Start(unsigned char delay);
unsigned char AM2305_ReadByte();