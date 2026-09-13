#include "stm32f10x.h"                  // Device header

uint16_t MyDMA_Size;

void MYDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size)
{
	MyDMA_Size = Size;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitTypeDef DMA_Initstructrue;
	DMA_Initstructrue.DMA_PeripheralBaseAddr = AddrA;//外设站点寄存器
	DMA_Initstructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_Initstructrue.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_Initstructrue.DMA_MemoryBaseAddr = AddrB;//接收设备
	DMA_Initstructrue.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_Initstructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_Initstructrue.DMA_DIR = DMA_DIR_PeripheralSRC;//传输方向
	DMA_Initstructrue.DMA_BufferSize = Size;//传数计数器
	DMA_Initstructrue.DMA_Mode = DMA_Mode_Normal;//是否自动重装
	DMA_Initstructrue.DMA_M2M = DMA_M2M_Enable;//触发模式
	DMA_Initstructrue.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1, &DMA_Initstructrue);
	
	DMA_Cmd(DMA1_Channel1,DISABLE);
	
}

void MYDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1,MyDMA_Size);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);

}
