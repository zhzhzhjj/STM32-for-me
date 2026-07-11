#include "stm32f10x.h"                  // Device header

void PWM_Init2(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitSturcture;
	TIM_OCStructInit(&TIM_OCInitSturcture);
	TIM_OCInitSturcture.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitSturcture.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitSturcture.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitSturcture.TIM_Pulse = 0;//ccr
	TIM_OC3Init(TIM3,&TIM_OCInitSturcture);
	TIM_Cmd(TIM3,ENABLE);
	
}


void PWM_2SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM3, Compare);
}