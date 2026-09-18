#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "Car.h"

uint8_t KeyNum;


int main(void)
{
	OLED_Init();
	Car_Init();
	while(1)
	{
		Go_Ahead();
	}
}
