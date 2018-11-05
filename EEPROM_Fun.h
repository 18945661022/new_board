/*--------------------------------------
主程序需要创建一个512字节的缓冲数组
如：unsigned char xdata EEPROM_Buffer[512];
--------------------------------------*/
#include "reg51.h"
#include "intrins.h"

/*Declare SFR associated with the IAP */
sfr IAP_DATA    =   0xC2;           //Flash data register
sfr IAP_ADDRH   =   0xC3;           //Flash address HIGH
sfr IAP_ADDRL   =   0xC4;           //Flash address LOW
sfr IAP_CMD     =   0xC5;           //Flash command register
sfr IAP_TRIG    =   0xC6;           //Flash command trigger
sfr IAP_CONTR   =   0xC7;           //Flash control register

/*Define ISP/IAP/EEPROM command*/
#define CMD_IDLE    0               //Stand-By
#define CMD_READ    1               //Byte-Read
#define CMD_PROGRAM 2               //Byte-Program
#define CMD_ERASE   3               //Sector-Erase

/*Define ISP/IAP/EEPROM operation const for IAP_CONTR*/
//#define ENABLE_IAP 0x80           //if SYSCLK<30MHz
//#define ENABLE_IAP 0x81           //if SYSCLK<24MHz
//#define ENABLE_IAP 0x82            //if SYSCLK<20MHz
#define ENABLE_IAP 0x83           //if SYSCLK<12MHz
//#define ENABLE_IAP 0x84           //if SYSCLK<6MHz
//#define ENABLE_IAP 0x85           //if SYSCLK<3MHz
//#define ENABLE_IAP 0x86           //if SYSCLK<2MHz
//#define ENABLE_IAP 0x87           //if SYSCLK<1MHz

#define IAP_ADDRESS_0 0x0000

void IapIdle();
unsigned char IapReadByte(unsigned int addr);
void IapProgramByte(unsigned int addr, unsigned char dat);
void IapEraseSector(unsigned int addr);
void GetSector(unsigned char iap_num,unsigned char* EEPROM_Buffer);	      //参数扇区号和暂存数组
void WriteSector(unsigned char iap_num,unsigned char* EEPROM_Buffer);