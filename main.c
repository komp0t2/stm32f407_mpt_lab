#include "GPIO_Library.h"
#include "stm32f407xx.h"
#include "stm32f4xx_adc.h"
#include "timer.h"
void init()
{
    GPIO_PinConfigure(GPIOA, 6, GPIO_MODE_ANALOG, GPIO_SPEED_HIGH, GPIO_PULL_NOT, 0);
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    ADC_InitTypeDef ADC_Structure;
    ADC_StructInit(&ADC_Structure);
    ADC_Structure.ADC_Resolution = ADC_Mode_Independent;
    ADC_Structure.ADC_ScanConvMode = DISABLE;
    ADC_Structure.ADC_ContinuousConvMode = DISABLE;
    ADC_Structure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_Structure.ADC_NbrOfConversion = 1;
    ADC_Structure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
    ADC_Init(ADC1, &ADC_Structure);
    ADC_Cmd(ADC1, ENABLE);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_56Cycles);
}
int main()
{
    while(1)
    {
        init();
        volatile uint16_t val = 0;
        while(1)
        {
            ADC_SoftwareStartConv(ADC1);
            while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET) {};
            val = ADC_GetConversionValue(ADC1);
        }
    }
}