#include "GPIO_Library.h"
#include "stm32f407xx.h"
#include "timer.h"
int main()
{
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    timer_init(TIM1, 0, 100, 72);
    GPIO_PinConfigure(GPIOA, 8, GPIO_MODE_AF, GPIO_SPEED_VERYHIGH, GPIO_PULL_NOT, GPIO_OUTCONF_OPENDRAIN);
    GPIO_PinAfConfig(GPIOA, 8, 1);
    TIM1->CCER |= TIM_CCER_CC1E;
    TIM1->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
    timer_enable(TIM1);

    while (1)
    {
    }
}