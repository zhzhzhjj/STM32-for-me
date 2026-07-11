#include "stm32f10x.h"                  // Device header
#include "OLED.h"

int main()
{
	OLED_Init();
	OLED_ShowString(1,1,"I Love You");
	OLED_ShowString(2,1,"(#-.-#)");
	OLED_ShowString(3,1,"(o.O)");
	OLED_ShowString(4,1,"(Orz)");
	OLED_ShowString(4,8,"(*_*)");
	while(1)
	{
		
	}
}