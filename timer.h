#include "stm32f4xx.h"
#ifndef __timer_h
#define __timer_h

#ifndef mybool
#define mybool
typedef enum
{
    false,
    true
} bool;
#endif

bool timer_init(TIM_TypeDef *TIMx, uint16_t CR1, uint16_t CNT, uint16_t PSC)
{
    TIMx->CR1 = CR1;  //Регистр управления
    TIMx->ARR = CNT - 1;  //До какого числа считает счетчик (-1 т.к фактически таймер сбросится на значении CNT+1)
    TIMx->PSC = PSC - 1;  //Предделитель системной частоты (-1 аналогично ARR)
    return true;
}
bool timer_disable(TIM_TypeDef *TIMx)
{
    TIMx->CR1 &= ~((uint16_t)0x1); //Выключение таймера
    return true;
}

bool timer_enable(TIM_TypeDef *TIMx)
{
    TIMx->CR1 |= (uint16_t)0x1; //Включение таймера
    return true;
}
#endif