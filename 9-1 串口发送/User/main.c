#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Serial.h"


int main()
{
	OLED_Init();
	Serial_Init();
	
//	Serial_SendByte(0x41);
//	
//	uint8_t MyArray[] = {0x41,0x42,0x43};
//	
//	Serial_SendArray(MyArray , 3);
//	
//	Serial_SendString("\r\nNum1=");
//	
//	Serial_SendNumber(111, 3);
	
	Serial_Printf("Num = %d\r\n",3545);
	
	while(1)
	{
		
	}
}