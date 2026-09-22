#include "stm32f10x.h"                  // Device header
#include "Delay.h"


void MYI2C_W_SCL(uint8_t BitValue)//封装对SCL的写入
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_0, (BitAction)BitValue);
	Delay_us(10);
}

void MYI2C_W_SDA(uint8_t BitValue)//封装对SDA的写入
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)BitValue);
	Delay_us(10);
}

uint8_t MYI2C_R_SDA(void)//由于SDA的写和读分别对应两个寄存器，所以写两个函数操作
{
	uint8_t BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1);
	Delay_us(10);
	return BitValue;
}

void MYI2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_0 |GPIO_Pin_1);
}

void MYI2C_Start(void)
{
	MYI2C_W_SDA(1);
	MYI2C_W_SCL(1);
	MYI2C_W_SDA(0);
	MYI2C_W_SCL(0);
}

void MYI2C_Stop(void)
{
	MYI2C_W_SDA(0);
	MYI2C_W_SCL(1);
	MYI2C_W_SDA(1);
}

void MYI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for(i = 0; i<8; i ++)
	{
		MYI2C_W_SDA(Byte & (0x80 >> i));
		MYI2C_W_SCL(1);
		MYI2C_W_SCL(0);
	}
}

uint8_t MYI2C_ReceiveByte(void)
{
	uint8_t Byte = 0x00;
	uint8_t i;
	MYI2C_W_SDA(1);
	for(i = 0;i<8;i++)
	{
		MYI2C_W_SCL(1);
		if(MYI2C_R_SDA() == 1){Byte |= (0x80 >> i);}
		MYI2C_W_SCL(0);
	}
	return Byte;
}


void MYI2C_SendAck(uint8_t AckBit)
{
	MYI2C_W_SDA(AckBit);
	MYI2C_W_SCL(1);
	MYI2C_W_SCL(0);
}

uint8_t MYI2C_ReceiveAck(void)
{
	uint8_t AckBit;
	MYI2C_W_SDA(1);
	MYI2C_W_SCL(1);
	AckBit = MYI2C_R_SDA();
	MYI2C_W_SCL(0);
	return AckBit;
}