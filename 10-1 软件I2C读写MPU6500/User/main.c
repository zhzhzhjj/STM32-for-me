#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "MYI2C.h"
#include "MPU6500.h"

uint8_t ID;	
int16_t AX, AY, AZ, GX, GY, GZ;

int main()
{
	OLED_Init();
	MPU6500_Init();
	
	OLED_ShowString(1, 1, "ID:");		//显示静态字符串
	ID = MPU6500_GetID();				//获取MPU6500的ID号
	OLED_ShowHexNum(1, 4, ID, 2);
	
	while(1)
	{
		MPU6500_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);		//获取MPU6050的数据
		OLED_ShowSignedNum(2, 1, AX, 5);					//OLED显示数据
		OLED_ShowSignedNum(3, 1, AY, 5);
		OLED_ShowSignedNum(4, 1, AZ, 5);
		OLED_ShowSignedNum(2, 8, GX, 5);
		OLED_ShowSignedNum(3, 8, GY, 5);
		OLED_ShowSignedNum(4, 8, GZ, 5);
	}
}