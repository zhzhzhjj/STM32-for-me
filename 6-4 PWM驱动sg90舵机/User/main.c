#include "stm32f10x.h"                  // Device header
#include "Servo.h"
#include "OLED.h"
#include "Delay.h"
#include "Key.h"

uint8_t Keynum;
float Angle;

int main()
{
	OLED_Init();
	Servo_Init();
	Key_Init();
	
	OLED_ShowString(1,1,"Angle:");
	
	while(1)
	{
		Keynum = Key_GetNum();
		if(Keynum == 1)
		{
			Angle += 30;
			if(Angle > 180)
			{
				Angle = 0;
			}
		}
		Servo_SetAngle(Angle);
		OLED_ShowNum(1,7,Angle,3);
	}
}