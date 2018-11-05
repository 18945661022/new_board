#include "18b20_Fun.h"
#include "Delay_Fun.h"
#include "Stc_Math.h"

/**************************************
��λDS18B20,������豸�Ƿ����
**************************************/
bit DS18B20_Reset()
{
    unsigned char DQI = 1;
    CY = 1;
    //while (CY)
	EA = 0;
    {
        DQ = 0;                     //�ͳ��͵�ƽ��λ�ź�
        DelayXus(165);            //��ʱ����480us
        DelayXus(165);
        DQ = 1;                     //�ͷ�������
        DelayXus(45);               //�ȴ�70us 
		CY = DQ;				    //����������
		DQI = CY;
	EA = 1;
        DelayXus(165);              //�ȴ��豸�ͷ�������
        DelayXus(165);
		return DQI;
    }
}

/**************************************
��DS18B20��1�ֽ�����
**************************************/
unsigned char DS18B20_ReadByte()
{
    unsigned char i;
    unsigned char dat = 0;

    for (i=0; i<8; i++)             //8λ������
    {
		EA = 0;
        dat >>= 1;
        DQ = 0;                     //��ʼʱ��Ƭ
        DelayXus(2);                //��ʱ�ȴ�
        DQ = 1;                     //׼������
        DelayXus(3);                //������ʱ
        if (DQ) dat |= 0x80;        //��ȡ����
		EA = 1;
        DelayXus(40);               //�ȴ�ʱ��Ƭ����
    }
    return dat;
}

/**************************************
��DS18B20д1�ֽ�����
**************************************/
void DS18B20_WriteByte(unsigned char dat)
{
    char i;

    for (i=0; i<8; i++)             //8λ������
    {
		EA = 0;
	    CY = dat&0x01;
		dat >>= 1;
        DQ = 0;                     //��ʼʱ��Ƭ
        DelayXus(2);                //��ʱ�ȴ�
        DQ = CY;                    //�ͳ�����
        DelayXus(40);               //�ȴ�ʱ��Ƭ����
        DQ = 1;                     //�ָ�������
        DelayXus(2);                //�ָ���ʱ
		EA = 1;
    }
}

void  DS18B20_Init()
{
	DS18B20_Reset();                //�豸��λ
	DS18B20_WriteByte(0xCC);        //����ROM����
    DS18B20_WriteByte(0x44);        //��ʼת������
    while (!DQ);                    //�ȴ�ת�����
    DS18B20_Reset();                //�豸��λ
    DS18B20_WriteByte(0xCC);        //����ROM����
    DS18B20_WriteByte(0xBE);        //���ݴ�洢������
}

/**************************************
��ȡ��������
**************************************/
unsigned char Get_Integer(unsigned char tph,unsigned char tpl)
{
	unsigned char Integer_Part1,i,j,temp1;		//temp��ʾ2�ļ�����
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
��ȡС������
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
ת�����ַ��� �̶�����11λ
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
	if((TPH>>8)&0x01)			    //�ж������¶�
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