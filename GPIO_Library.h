#include "stm32f4xx.h"
#ifndef __GPIO_LIBRARY_H
#define __GPIO_LIBRARY_H
#define e1 GPIO_PIN_OUT(GPIOE, 8, true);  // установка линии E в 1
#define e0 GPIO_PIN_OUT(GPIOE, 8, false);  // установка линии E в 0
#define rs1 GPIO_PIN_OUT(GPIOB, 0, true);  // установка линии RS в 1 (данные)
#define rs0 GPIO_PIN_OUT(GPIOB, 0, false);  // установка линии RS в 0 (команда)
#define rw1 GPIO_PIN_OUT(GPIOA, 4, true);  // установка линии RS в 1 (данные)
#define rw0 GPIO_PIN_OUT(GPIOA, 4, false);  // установка линии RS в 0 (команда)
#define deactivateRows GPIOD->ODR |= 0xF;  //Перевод PD0-PD3 в состояние HIGH
typedef enum
{
    KEY_ZERO     = 0x13,
    KEY_ONE      = 0x00,
    KEY_TWO      = 0x10,
    KEY_THREE    = 0x20,
    KEY_FOUR     = 0x01,
    KEY_FIVE     = 0x11,
    KEY_SIX      = 0x21,
    KEY_SEVEN    = 0x02,
    KEY_EIGHT    = 0x12,
    KEY_NINE     = 0x22,
    KEY_A        = 0x30,
    KEY_B        = 0x31,
    KEY_C        = 0x32,
    KEY_D        = 0x33,
    KEY_NUMBER   = 0x03,
    KEY_ASTERISK = 0x23,
} KEYBOARD_CODE_SYMBOL;
typedef enum
{
    LCD_ZERO     = 0x30,
    LCD_ONE      = 0x31,
    LCD_TWO      = 0x32,
    LCD_THREE    = 0x33,
    LCD_FOUR     = 0x34,
    LCD_FIVE     = 0x35,
    LCD_SIX      = 0x36,
    LCD_SEVEN    = 0x37,
    LCD_EIGHT    = 0x38,
    LCD_NINE     = 0x39,
    LCD_A        = 0x41,
    LCD_B        = 0x42,
    LCD_C        = 0x43,
    LCD_D        = 0x44,
    LCD_NUMBER   = 0x2A,
    LCD_ASTERISK = 0x23,
} LCD_CODE_SYMBOL;
#ifndef mybool
#define mybool
typedef enum
{
    false,
    true
} bool;
#endif
typedef enum
{
    GPIO_SPEED_LOW      = 0x00,  //Speed: 0 - Low; 1 - Medium; 2 - High; 3 - Very high
    GPIO_SPEED_MEDIUM   = 0x01,
    GPIO_SPEED_HIGH     = 0x02,
    GPIO_SPEED_VERYHIGH = 0x03
} GPIO_SPEED;
typedef enum
{
    GPIO_MODE_INPUT  = 0x00,  //Mode: 0 - Input; 1 - General purpose output; 2 - Alternative function; 3 - Analog;
    GPIO_MODE_OUTPUT = 0x01,
    GPIO_MODE_AF     = 0x02,
    GPIO_MODE_ANALOG = 0x03
} GPIO_MODE;
typedef enum
{
    GPIO_PULL_NOT  = 0x00,  //Pull-up resistor: 0 - Not pull; 1 - PullUp; 2 - PullDown;
    GPIO_PULL_UP   = 0x01,
    GPIO_PULL_DOWN = 0x02,
} GPIO_PULL;
typedef enum
{
    GPIO_OUTCONF_PUSHPULL  = 0x00,  //Output: 0 - PushPull; 1 - OpenDrain
    GPIO_OUTCONF_OPENDRAIN = 0x01,
} GPIO_OUTCONF;
void GPIO_PortClock(GPIO_TypeDef *GPIOx, bool enable)  //Включение тактирования GPIO
{
    if (enable)
    {
        if (GPIOx == GPIOA)
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        else if (GPIOx == GPIOB)
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
        else if (GPIOx == GPIOC)
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
        else if (GPIOx == GPIOD)
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
        else if (GPIOx == GPIOE)
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
        else if (GPIOx == GPIOF)
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
        else if (GPIOx == GPIOG)
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    }
    else
    {
        if (GPIOx == GPIOA)
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN;
        else if (GPIOx == GPIOB)
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN;
        else if (GPIOx == GPIOC)
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN;
        else if (GPIOx == GPIOD)
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN;
        else if (GPIOx == GPIOE)
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN;
        else if (GPIOx == GPIOF)
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOFEN;
        else if (GPIOx == GPIOG)
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOGEN;
    }
}
bool GPIO_GetPortClockState(GPIO_TypeDef *GPIOx)  //проверка тактирования GPIO
{

    if (GPIOx == GPIOA)
    {
        return ((RCC->AHB1ENR & (1U << RCC_AHB1ENR_GPIOAEN_Pos)) != 0U);
    }
    else if (GPIOx == GPIOB)
    {
        return ((RCC->AHB1ENR & (1U << RCC_AHB1ENR_GPIOBEN_Pos)) != 0U);
    }
    else if (GPIOx == GPIOC)
    {
        return ((RCC->AHB1ENR & (1U << RCC_AHB1ENR_GPIOCEN_Pos)) != 0U);
    }
    else if (GPIOx == GPIOD)
    {
        return ((RCC->AHB1ENR & (1U << RCC_AHB1ENR_GPIODEN_Pos)) != 0U);
    }
    else if (GPIOx == GPIOE)
    {
        return ((RCC->AHB1ENR & (1U << RCC_AHB1ENR_GPIOEEN_Pos)) != 0U);
    }
    else if (GPIOx == GPIOF)
    {
        return ((RCC->AHB1ENR & (1U << RCC_AHB1ENR_GPIOFEN_Pos)) != 0U);
    }
    else if (GPIOx == GPIOG)
    {
        return ((RCC->AHB1ENR & (1U << RCC_AHB1ENR_GPIOGEN_Pos)) != 0U);
    }

    return false;
}
bool GPIO_PinConfigure(GPIO_TypeDef *GPIOx, uint32_t num, GPIO_MODE mode, GPIO_SPEED speed, GPIO_PULL pull, GPIO_OUTCONF conf)
{

    if (GPIO_GetPortClockState(GPIOx) == false)
    {
        /* Enable GPIOx peripheral clock */
        GPIO_PortClock(GPIOx, true);
    }
    GPIOx->PUPDR &= ~(0x3 << num * 2U);
    GPIOx->PUPDR |= pull << num * 2U;
    GPIOx->OSPEEDR &= ~(0x3 << num * 2U);
    GPIOx->OSPEEDR |= speed << num * 2U;
    GPIOx->MODER &= ~(0x3 << num * 2U);
    GPIOx->MODER |= mode << num * 2U;
    if ((mode == GPIO_MODE_OUTPUT) || (mode == GPIO_MODE_AF))
    {
        GPIOx->OTYPER &= ~(0x1 << num);
        GPIOx->OTYPER |= conf << num;
    }
    else
        GPIOx->OTYPER &= ~(0x1 << num);

    return true;
}
bool GPIO_PinAfConfig(GPIO_TypeDef *GPIOx, uint32_t num, uint32_t af)  //Установка альтернативной функции для GPIO (af - номер функции)
{
    if (num <= 7)
    {
        GPIOx->AFR[0] &= ~(0xF << num * 4U);
        GPIOx->AFR[0] |= ((af & 0xF) << num * 4U);
    }
    else if ((num <= 15) && (num > 7))
    {
        GPIOx->AFR[1] &= ~(0xF << (num - 8) * 4U);
        GPIOx->AFR[1] |= ((af & 0xF) << (num - 8) * 4U);
    }
    return true;
}
void DELAY(unsigned long Time)  //Задержка
{
    unsigned long int Iterator;
    for (Iterator = 0; Iterator < (((SystemCoreClock / 28000) * Time) / 1000); Iterator++)
    {
        __asm("nop");
    }
}
void delay(void)

{
    uint16_t i;
    for (i = 0; i < 100; i++)
        ;
}

void GPIO_PIN_OUT(GPIO_TypeDef *GPIOx, uint32_t num, bool pos)  //Установка значения порта
{
    if (pos)
    {
        GPIOx->ODR |= 0x1 << num;
    }
    else
    {
        GPIOx->ODR &= ~(0x1 << num);
    }
}
int GPIO_PIN_IN(GPIO_TypeDef *GPIOx, uint32_t num)  //Проверка состояния входа вывода GPIO
{
    return ((GPIOx->IDR & (1U << num)) != 0U);
}
int GPIO_PIN_IN_KEY(GPIO_TypeDef *GPIOx, uint32_t num)  //Проверка отстутствия дребезга на входе вывода GPIO
{
    if (GPIO_PIN_IN(GPIOx, num) == 0)
        if (GPIO_PIN_IN(GPIOx, num) == 0)
            if (GPIO_PIN_IN(GPIOx, num) == 0)
                if (GPIO_PIN_IN(GPIOx, num) == 0)
                    return GPIO_PIN_IN(GPIOx, num);
    return -1;
}
uint16_t get_key()  //Получение кода клавиши (-1 - нажатие меньше или больше одной кнопки)
{
    uint16_t key_Code = 0;  //Код клавиши
    deactivateRows;
    for (int x = 0; x < 4; x++)
    {
        GPIO_PIN_OUT(GPIOD, x, false);
        for (int y = 0; y < 4; y++)
        {
            if (GPIO_PIN_IN(GPIOD, y + 10) == 0)
            {
                DELAY(10);
                if (GPIO_PIN_IN_KEY(GPIOD, y + 10) == 0)
                {
                    key_Code += (x << 4) + y + 0x100;
                }
            }
        }
        GPIO_PIN_OUT(GPIOD, x, true);
    }
    if ((key_Code >= 0x100) && (key_Code < 0x200))
        return (key_Code & 0xFF);
    else
        return -1;
}
void LCD_COMMAND(uint8_t num)  //Команды управления дисплея
{
    int a[8];
    int i = 0;
    while (i <= 7)
    {
        a[i] = num % 2;
        i++;
        num = num / 2;
    }
    rs0;
    rw0;
    e1;
    delay();
    if (a[0] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 0, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 0, false);
    }
    if (a[1] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 1, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 1, false);
    }
    if (a[2] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 2, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 2, false);
    }
    if (a[3] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 3, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 3, false);
    }
    if (a[4] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 4, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 4, false);
    }
    if (a[5] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 5, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 5, false);
    }
    if (a[6] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 6, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 6, false);
    }
    if (a[7] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 7, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 7, false);
    }
    delay();
    e0;
    DELAY(1000);
}
void LCD_WRITE(uint8_t num)  //Запись данных в дисплей
{
    int a[8];
    int i = 0;
    while (i <= 7)
    {
        a[i] = num % 2;
        i++;
        num = num / 2;
    }
    rs1;
    e1;
    delay();
    if (a[0] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 0, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 0, false);
    }
    if (a[1] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 1, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 1, false);
    }
    if (a[2] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 2, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 2, false);
    }
    if (a[3] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 3, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 3, false);
    }
    if (a[4] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 4, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 4, false);
    }
    if (a[5] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 5, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 5, false);
    }
    if (a[6] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 6, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 6, false);
    }
    if (a[7] == 1)
    {
        GPIO_PIN_OUT(GPIOC, 7, true);
    }
    else
    {
        GPIO_PIN_OUT(GPIOC, 7, false);
    }
    delay();
    e0;
    DELAY(5000);
}
void DISPLAY_ON()  //Инициализация дисплея
{
    GPIO_PinConfigure(GPIOB, 0, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    GPIO_PinConfigure(GPIOE, 8, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    GPIO_PinConfigure(GPIOC, 0, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    GPIO_PinConfigure(GPIOC, 1, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    GPIO_PinConfigure(GPIOC, 2, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    GPIO_PinConfigure(GPIOC, 3, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    GPIO_PinConfigure(GPIOC, 4, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    GPIO_PinConfigure(GPIOC, 5, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    GPIO_PinConfigure(GPIOC, 6, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    GPIO_PinConfigure(GPIOC, 7, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    DELAY(25000);
    LCD_COMMAND(0x30);
    delay();
    LCD_COMMAND(0x30);
    delay();
    LCD_COMMAND(0x30);
    delay();
    LCD_COMMAND(0x30);
    delay();
    LCD_COMMAND(0x30);
    delay();
    LCD_COMMAND(0x38);
    delay();
    LCD_COMMAND(0x08);
    delay();
    LCD_COMMAND(0x80);
    delay();
    LCD_COMMAND(0x01);
    DELAY(5000);
    LCD_COMMAND(0x06);
    delay();
    LCD_COMMAND(0x02);
    delay();
    LCD_COMMAND(0x0C);
    delay();
}
void init_keyboard()
{
    GPIO_PinConfigure(GPIOD, 0, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    GPIO_PinConfigure(GPIOD, 1, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    GPIO_PinConfigure(GPIOD, 2, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    GPIO_PinConfigure(GPIOD, 3, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);

    GPIO_PinConfigure(GPIOD, 10, GPIO_MODE_INPUT, GPIO_SPEED_LOW, GPIO_PULL_UP, 0);
    GPIO_PinConfigure(GPIOD, 11, GPIO_MODE_INPUT, GPIO_SPEED_LOW, GPIO_PULL_UP, 0);
    GPIO_PinConfigure(GPIOD, 12, GPIO_MODE_INPUT, GPIO_SPEED_LOW, GPIO_PULL_UP, 0);
    GPIO_PinConfigure(GPIOD, 13, GPIO_MODE_INPUT, GPIO_SPEED_LOW, GPIO_PULL_UP, 0);
}
#endif