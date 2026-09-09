#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "AD.H"
#include "Delay.h"
#include "PWM.h"

uint16_t ADValue;
float Voltage;
uint16_t a;

int main()
{
	OLED_Init();
	AD_Init();
	PWM_Init();
	
	OLED_ShowString(1,1,"AD_Value:");
	OLED_ShowString(2,1,"Voltage:0.00V");
	OLED_ShowString(3,1,"Light:");
	OLED_ShowString(3,10,"%");
	
	while(1)
	{
		ADValue = AD_GetValue();
		Voltage = (float)ADValue / 4095 * 3;
		OLED_ShowNum(1,10,ADValue,4);
		OLED_ShowNum(2,9,Voltage,1);
		OLED_ShowNum(2,11,(uint16_t)(Voltage * 100) % 100,2);
		PWM_SetCompare1((uint32_t)ADValue * 100 / 4095);
		a = (uint16_t)((uint32_t)ADValue * 100 / 4095);
		OLED_ShowNum(3,7,a,3);
		
		Delay_ms(100);
	}
}