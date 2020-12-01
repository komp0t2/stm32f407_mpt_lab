#include "GPIO_Library.h"
#include "stm32f407xx.h"
void init_pin();
void transformation(uint8_t *buffer)
{
    LCD_COMMAND(0x1);
    for (int i = 0; i < 8; i++)
    {
        LCD_WRITE(buffer[i]*2+128);
    }
}
int main()
{
    uint8_t keys_symb[16] = {
        KEY_ZERO,
        KEY_ONE,
        KEY_TWO,
        KEY_THREE,
        KEY_FOUR,
        KEY_FIVE,
        KEY_SIX,
        KEY_SEVEN,
        KEY_EIGHT,
        KEY_NINE,
        KEY_A,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_NUMBER,
        KEY_ASTERISK,
    };
    uint8_t LCD_symb[16] = {
        LCD_ZERO,
        LCD_ONE,
        LCD_TWO,
        LCD_THREE,
        LCD_FOUR,
        LCD_FIVE,
        LCD_SIX,
        LCD_SEVEN,
        LCD_EIGHT,
        LCD_NINE,
        LCD_A,
        LCD_B,
        LCD_C,
        LCD_D,
        LCD_NUMBER,
        LCD_ASTERISK,
    };
    uint8_t input_buffer[8];
    int size_buffer = 0;
    DISPLAY_ON();
    init_keyboard();
    GPIO_PinConfigure(GPIOB, 7, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    GPIO_PinConfigure(GPIOE, 0, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    GPIO_PinConfigure(GPIOB, 8, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
    int16_t key_code = -1;
    while (1)
    {
        //	DISPLAY_BITS(767);
        //	GPIO_PIN_OUT(GPIOB,7, true);
        //	DELAY(1000000);
        //	GPIO_PIN_OUT(GPIOB,7, false);
        //	DELAY(1000000);
        key_code = get_key();
        if (key_code != -1)
        {
            for (int i = 0; i < 16; i++)
            {
                if (key_code == keys_symb[i])
                {
                    //GPIO_PIN_OUT(GPIOB, 8, true);
                    if (key_code == KEY_C)
                    {
                        LCD_COMMAND(0x1);
                        size_buffer = 0;
                    }

                    else if (key_code == KEY_A)
                    {
                        if (size_buffer == 8)
                            transformation(input_buffer);
                    }
                    else if (size_buffer < 8)
                    {
                        input_buffer[size_buffer] = LCD_symb[i];
                        size_buffer++;
                        LCD_WRITE(LCD_symb[i]);
                    }
                    DELAY(250000);
                    break;
                }
            }
            key_code = -1;
        }
        else
        {
            //GPIO_PIN_OUT(GPIOB, 8, false);
        }
    }
}