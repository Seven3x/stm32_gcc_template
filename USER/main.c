#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "stm32f10x_gpio.h"

int main()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	delay_init();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
    while(1)
	{
		PAout(8) = 1;
		delay_ms(200);
		PAout(8) = 0;
		delay_ms(200);
	}
	
}
   