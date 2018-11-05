#include "AM2305.h"
#include "Delay_Fun.h"

/**************************************
AM2305一次采集最开始操作及结果返回
**************************************/
unsigned char AM2305_Start(unsigned char delay)
{
	unsigned int i;
	//先给出低电平
	Sensor_SDA = 0;
	Delayms(delay);
	//释放总线 (Min=30us Max=50us)
	Sensor_SDA = 1; 	
	DelayXus(22);//延时34us
	//判断传感器响应信号
	if(Sensor_SDA ==0)
	{
		i = 300;
		while(!Sensor_SDA)
		{
			if(i--==0)
			{
				return 2;      //80us低电平没出来
			}
		}
		i = 300;
		while(Sensor_SDA)
		{
			if(i--==0)
			{
				EA = 1;
				return 3;      //80us高电平没出来
			}
		}
		return 0;        //成功，准备接受数据
	}
	else
	{
		return 1;	  //断路错误（很有可能）
	}
}

/**************************************
AM2305字节获取，失败的话返回0值
**************************************/
unsigned char AM2305_ReadByte()
{
	unsigned char i,cnt;
	unsigned char buffer,tmp;
	buffer = 0;
	//循环读取
	for(i=0;i<8;i++)
	{
		cnt = 400;
		while(!Sensor_SDA)
		{
			if(cnt--==0)
			{
				return 0;      //50us低电平没出来
			}
		}
		//延时Min=26us Max50us 跳过数据"0" 的高电平
		DelayXus(22); //延时34us 
		//判断传感器发送数据位
		tmp =0;
		if(Sensor_SDA)	 
		{
		  tmp = 1;
		}
		cnt = 400;
		while(Sensor_SDA)
		{
			if(cnt--==0)
			{
				return 0;      //（不超过80us）高电平没出来
			}
		}
		buffer <<=1;
		buffer |= tmp;   
	}
	return buffer;
}