#include "GPIO_Library.h"
#include "stm32f407xx.h"
#include "stm32f4xx_adc.h"
#include "timer.h"
int main()
{
    
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  //Тактирование таймера
    timer_init(TIM1, 0, 80, 100);  //Инициализация таймера предделитель 16, счетчик 100
    GPIO_PinConfigure(GPIOA, 8, GPIO_MODE_AF, GPIO_SPEED_VERYHIGH, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);  //Конфигурация PA8
    GPIO_PinAfConfig(GPIOA, 8, 1);  //AF1 альтернативная функция PA8
    GPIO_PinConfigure(GPIOA, 7, GPIO_MODE_AF, GPIO_SPEED_VERYHIGH, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);  //Конфигурация PA8
    GPIO_PinAfConfig(GPIOA, 7, 1);  //AF1 альтернативная функция PA7
    TIM1->CCR1 = 8;  //Заполнение
    TIM1->BDTR |= TIM_BDTR_MOE;  //Разрешение на использования выхода с регистра сравнения как выход порта GPIO
    TIM1->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);  //Режим ШИМ1 (Прямой шим)
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1NE;  //Активация канала с регистра сравнения
    timer_enable(TIM1);  //Активация таймера
    while (1)
    {
    }
}