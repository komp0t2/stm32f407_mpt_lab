#include "stm32f407xx.h"
#include "timer.h"
#include "GPIO_Library.h"
int main()
{
    while (1)
    {
	GPIOA->AFR[1];
	timer_init(TIM1,0,100,72);
	GPIO_PinAfConfig(GPIO);
    }
}