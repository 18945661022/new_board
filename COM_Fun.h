/*------------------------------------
SCON     PARITYBIT(校验)	  校验位初始值
0x50     8位无校验    		   
0xda	 9位奇偶标记校验           1
0xd2     9位SPACE校验              0
--------------------------------------*/
#include "reg51.h"
#include "intrins.h"

/*Define UART parity mode*/
#define NONE_PARITY     0   //None parity
#define ODD_PARITY      1   //Odd parity
#define EVEN_PARITY     2   //Even parity
#define MARK_PARITY     3   //Mark parity
#define SPACE_PARITY    4   //Space parity

#define PARITYBIT EVEN_PARITY   //Testing even parity

//sfr SCON = 0x98;
//sfr SBUF = 0x99;

/*Declare SFR associated with the UART2 */
sfr AUXR  = 0x8e;           //Auxiliary register
sfr S2CON = 0x9a;           //UART2 control register
sfr S2BUF = 0x9b;           //UART2 data buffer
sfr BRT   = 0x9c;           //Baudrate generator
sfr IE2   = 0xaf;           //Interrupt control 2

#define S2RI  0x01          //S2CON.0
#define S2TI  0x02          //S2CON.1
#define S2RB8 0x04          //S2CON.2
#define S2TB8 0x08          //S2CON.3


void SendData1(unsigned char dat);
void SendString1(char *s);

void SendData2(unsigned char dat);
void SendString2(char *s);

void Timer_Uart_Init();		  //定时器、串口初始化
