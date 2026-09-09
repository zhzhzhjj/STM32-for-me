#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "AD.H"
#include "Delay.h"

uint16_t ADValue;
float Voltage;

int main()
{
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1,1,"AD_Value:");
	OLED_ShowString(2,1,"Voltage:0.00V");
	
	while(1)
	{
		ADValue = AD_GetValue();
		Voltage = (float)ADValue / 4095 * 3;
		OLED_ShowNum(1,10,ADValue,4);
		OLED_ShowNum(2,9,Voltage,1);
		OLED_ShowNum(2,11,(uint16_t)(Voltage * 100) % 100,2);
		Delay_ms(100);
	}
}