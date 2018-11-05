#include "AM2305.h"
#include "Delay_Fun.h"

/**************************************
AM2305һ�βɼ��ʼ�������������
**************************************/
unsigned char AM2305_Start(unsigned char delay)
{
	unsigned int i;
	//�ȸ����͵�ƽ
	Sensor_SDA = 0;
	Delayms(delay);
	//�ͷ����� (Min=30us Max=50us)
	Sensor_SDA = 1; 	
	DelayXus(22);//��ʱ34us
	//�жϴ�������Ӧ�ź�
	if(Sensor_SDA ==0)
	{
		i = 300;
		while(!Sensor_SDA)
		{
			if(i--==0)
			{
				return 2;      //80us�͵�ƽû����
			}
		}
		i = 300;
		while(Sensor_SDA)
		{
			if(i--==0)
			{
				EA = 1;
				return 3;      //80us�ߵ�ƽû����
			}
		}
		return 0;        //�ɹ���׼����������
	}
	else
	{
		return 1;	  //��·���󣨺��п��ܣ�
	}
}

/**************************************
AM2305�ֽڻ�ȡ��ʧ�ܵĻ�����0ֵ
**************************************/
unsigned char AM2305_ReadByte()
{
	unsigned char i,cnt;
	unsigned char buffer,tmp;
	buffer = 0;
	//ѭ����ȡ
	for(i=0;i<8;i++)
	{
		cnt = 400;
		while(!Sensor_SDA)
		{
			if(cnt--==0)
			{
				return 0;      //50us�͵�ƽû����
			}
		}
		//��ʱMin=26us Max50us ��������"0" �ĸߵ�ƽ
		DelayXus(22); //��ʱ34us 
		//�жϴ�������������λ
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
				return 0;      //��������80us���ߵ�ƽû����
			}
		}
		buffer <<=1;
		buffer |= tmp;   
	}
	return buffer;
}