#include "GPIO_Library.h"
#include "stm32f407xx.h"
#include "stm32f4xx_adc.h"
#include "timer.h"
volatile uint16_t val = 0;
void init()
{
    DISPLAY_ON();
    GPIO_PinConfigure(GPIOA, 6, GPIO_MODE_ANALOG, GPIO_SPEED_HIGH, GPIO_PULL_NOT, 0);
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    ADC_InitTypeDef ADC_Structure;
    ADC_StructInit(&ADC_Structure);
    ADC_Structure.ADC_Resolution = ADC_Resolution_12b;
    ADC_Structure.ADC_ScanConvMode = DISABLE;
    ADC_Structure.ADC_ContinuousConvMode = DISABLE;
    ADC_Structure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_Structure.ADC_NbrOfConversion = 1;
    ADC_Structure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
    ADC_Init(ADC1, &ADC_Structure);
    ADC_Cmd(ADC1, ENABLE);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_15Cycles);
    //Инициализация таймера для вывода данных на дисплей
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  //Тактирование таймера
    timer_init(TIM1, 0, 1600, 5000);  //Инициализация таймера предделитель 16, счетчик 100
    timer_enable(TIM1);  //Активация таймера
    TIM1->DIER |= TIM_DIER_UIE;
}
int main()
{
    init();
    while(1)
    {
        ADC_SoftwareStartConv(ADC1);
        while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET) {};
        NVIC_DisableIRQ(TIM1_UP_TIM10_IRQn);
        val = ADC_GetConversionValue(ADC1);
        NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
    }
}
void TIM1_UP_TIM10_IRQHandler(void)
{
    uint16_t temp_val = (uint16_t)((double)val * 0.0008058608058 * 10000 + 0.00005);
    uint16_t buffer[5];
    LCD_COMMAND(0x1);
    int i = 0;
    do
    {
        buffer[i++] = (uint16_t)temp_val % 10 + 0x30;
        temp_val = (uint16_t)temp_val / 10;
    } while(i < 5);
    while(i >= 0)
    {
        LCD_WRITE(buffer[i--]);
        if(i == 3) LCD_WRITE(0x2E);
    }
    LCD_WRITE(0x56);
    TIM1->SR &= ~TIM_SR_UIF;
}