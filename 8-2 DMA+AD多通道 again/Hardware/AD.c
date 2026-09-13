#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[4];

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);

	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//连续模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//扫描模式
	ADC_InitStructure.ADC_NbrOfChannel = 4;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	
	DMA_InitTypeDef DMA_Initstructrue;
	DMA_Initstructrue.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//外设站点寄存器
	DMA_Initstructrue.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_Initstructrue.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_Initstructrue.DMA_MemoryBaseAddr = (uint32_t)AD_Value;//接收设备
	DMA_Initstructrue.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_Initstructrue.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_Initstructrue.DMA_DIR = DMA_DIR_PeripheralSRC;//传输方向
	DMA_Initstructrue.DMA_BufferSize = 4;//传数计数器
	DMA_Initstructrue.DMA_Mode = DMA_Mode_Circular;//是否自动重装
	DMA_Initstructrue.DMA_M2M = DMA_M2M_Disable;//触发模式
	DMA_Initstructrue.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1, &DMA_Initstructrue);
	
	DMA_Cmd(DMA1_Channel1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

}
