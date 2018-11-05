#include "18b20_Fun.h"
#include "Delay_Fun.h"
#include "Stc_Math.h"

/**************************************
复位DS18B20,并检测设备是否存在
**************************************/
bit DS18B20_Reset()
{
    unsigned char DQI = 1;
    CY = 1;
    //while (CY)
	EA = 0;
    {
        DQ = 0;                     //送出低电平复位信号
        DelayXus(165);            //延时至少480us
        DelayXus(165);
        DQ = 1;                     //释放数据线
        DelayXus(45);               //等待70us 
		CY = DQ;				    //检测存在脉冲
		DQI = CY;
	EA = 1;
        DelayXus(165);              //等待设备释放数据线
        DelayXus(165);
		return DQI;
    }
}

/**************************************
从DS18B20读1字节数据
**************************************/
unsigned char DS18B20_ReadByte()
{
    unsigned char i;
    unsigned char dat = 0;

    for (i=0; i<8; i++)             //8位计数器
    {
		EA = 0;
        dat >>= 1;
        DQ = 0;                     //开始时间片
        DelayXus(2);                //延时等待
        DQ = 1;                     //准备接收
        DelayXus(3);                //接收延时
        if (DQ) dat |= 0x80;        //读取数据
		EA = 1;
        DelayXus(40);               //等待时间片结束
    }
    return dat;
}

/**************************************
向DS18B20写1字节数据
**************************************/
void DS18B20_WriteByte(unsigned char dat)
{
    char i;

    for (i=0; i<8; i++)             //8位计数器
    {
		EA = 0;
	    CY = dat&0x01;
		dat >>= 1;
        DQ = 0;                     //开始时间片
        DelayXus(2);                //延时等待
        DQ = CY;                    //送出数据
        DelayXus(40);               //等待时间片结束
        DQ = 1;                     //恢复数据线
        DelayXus(2);                //恢复延时
		EA = 1;
    }
}

void  DS18B20_Init()
{
	DS18B20_Reset();                //设备复位
	DS18B20_WriteByte(0xCC);        //跳过ROM命令
    DS18B20_WriteByte(0x44);        //开始转换命令
    while (!DQ);                    //等待转换完成
    DS18B20_Reset();                //设备复位
    DS18B20_WriteByte(0xCC);        //跳过ROM命令
    DS18B20_WriteByte(0xBE);        //读暂存存储器命令
}

/**************************************
获取整数部分
**************************************/
unsigned char Get_Integer(unsigned char tph,unsigned char tpl)
{
	unsigned char Integer_Part1,i,j,temp1;		//temp表示2的几次幂
	Integer_Part1 = 0;
	temp1 = 1;
	for(i=0;i<=2;i++)
	{
		if((tph>>i)&0x01)
		{
			for(j=0;j<i;j++)
			{
				temp1 = temp1*2;
			}
			Integer_Part1 = Integer_Part1 + temp1*16;
			temp1 = 1;
		}
	}
	for(i=0;i<=3;i++)
	{
		if((tpl>>(i+4))&0x01)
		{
			for(j=0;j<i;j++)
			{
				temp1 = temp1*2;
			}
			Integer_Part1 = Integer_Part1 + temp1;
			temp1 = 1;
		}
	}
	return 	Integer_Part1;
}

/**************************************
获取小数部分
**************************************/
unsigned int Get_Decimal(unsigned char tpl)
{
	unsigned int Decimal_Part1;
	Decimal_Part1 = 0;
	if((tpl>>3)&0x01)
	{
		Decimal_Part1 = Decimal_Part1 + 5000;	
	}
	if((tpl>>2)&0x01)
	{
		Decimal_Part1 = Decimal_Part1 + 2500;	
	}
	if((tpl>>1)&0x01)
	{
		Decimal_Part1 = Decimal_Part1 + 1250;	
	}
	if(tpl&0x01)
	{
		Decimal_Part1 = Decimal_Part1 + 625;	
	}
	return Decimal_Part1;
}

/**************************************
转换成字符串 固定长度11位
*************************************
void GetTempString(unsigned char TPH,unsigned char TPL,unsigned char* Array)
{
	unsigned int k;
	unsigned int INTEGER_PART,DECIMAL_PART;
	unsigned char xdata ArrayString[10] = {'0','1','2','3','4','5','6','7','8','9'};
	if(Array == 0x00)
	{
		return ;
	}
	if((TPH>>8)&0x01)			    //判断正负温度
	{
		Array[0] = '-';
	}
	else
	{
		Array[0] = '+';
	}
	INTEGER_PART = 	Get_Integer(TPH,TPL);
	DECIMAL_PART = Get_Decimal(TPL);
	EA = 0;
	WordToStr(INTEGER_PART,&Array[1],3);
	WordToStr(DECIMAL_PART,&Array[5],4);
	EA =1;
	Array[4] = '.';
	Array[9] = 0xdf;
	Array[10] = 'C';

	return ;
}
*/