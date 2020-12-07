#include "GPIO_Library.h"
#include "LCD_Library.h"
#include "stm32f407xx.h"
void transformation(LCD_InitTypeDef *LCD, int* buffer,int* sign)
{
	LCD_Clear(LCD);
	for (int i = 0; i < 8; i++)
	{
		int size_numb = 0;
		int tmp= 0;
		buffer[i] = buffer[i]*sign[i]*2+128;
		if ((buffer[i] >= 0)&&(sign[i] == - 1))
		{
			sign[i] = 1;
		}
		else if (buffer[i] < 0)
		{
			buffer[i]*=-1;
		}
		for (int tmp_numb = buffer[i]; tmp_numb > 0; size_numb++)
		{
			tmp_numb /= 10;
		}
		for (int j = 0; j < size_numb; j++)
		{
			tmp = tmp * (j > 0 ? 10 : 1) + buffer[i]%10;
			buffer[i]/=10;
		}
		if(sign[i] == -1)LCD_WRITE(LCD, 0x2D, true);
		for (int k = 0; k < size_numb; k++)
		{
			LCD_WRITE(LCD, tmp % 10 + 0x30, true);
			tmp/=10;
		}
		if(i!=7)LCD_WRITE(LCD, 0x20, true);
	}
}
int main()
{
	static uint8_t keys_symb[16] = {
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
	static uint8_t LCD_symb[16] = {
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
	int numbs_buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	//
	LCD_InitTypeDef LCD1;
	int sign_buffer[8]	  = {1, 1, 1, 1, 1, 1, 1, 1};
	int size_buffer		  = 0;
	bool space_allow_flag = false;
	int size_numb		  = 0;
	DISPLAY_ON(&LCD1);
	init_keyboard();
	GPIO_PinConfigure(GPIOB, 7, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
	GPIO_PinConfigure(GPIOE, 0, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
	GPIO_PinConfigure(GPIOB, 8, GPIO_MODE_OUTPUT, GPIO_SPEED_LOW, GPIO_PULL_NOT, GPIO_OUTCONF_PUSHPULL);
	int16_t key_code = -1;
	while (1)
	{
		//DISPLAY_BITS(767);
		//GPIO_PIN_OUT(GPIOB,7, true);
		//DELAY(1000000);
		//GPIO_PIN_OUT(GPIOB,7, false);
		//DELAY(1000000);
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
						LCD_Clear(&LCD1);
						for (int i = 0; i < 8; i++)
						{
							sign_buffer[i] = 1;
							numbs_buffer[i] = 0;
						}
						size_numb		 = 0;
						size_buffer		 = 0;
						space_allow_flag = false;
						
					}
					else if (key_code == KEY_A) //Up line
					{
						LCD_lineup(&LCD1);
					}
					else if (key_code == KEY_B) //down line
					{
						LCD_linedown(&LCD1);
					}
					else if (key_code == KEY_D) //down line
					{
						transformation(&LCD1, numbs_buffer, sign_buffer);
						size_buffer = 7;
						size_numb = 3;
					}
					else if (key_code == KEY_NUMBER) //BackspaceLCD
					{
						LCD_backspace(&LCD1);
						if ((size_numb == 0) && (size_buffer > 0) && (sign_buffer[size_buffer] == 1))
						{
							size_numb = 0;
							for (int tmp_numb = numbs_buffer[--size_buffer]; tmp_numb > 0; size_numb++) tmp_numb /= 10;
							space_allow_flag = true;
						}
						else if ((size_numb == 0) && (sign_buffer[size_buffer] == -1))
						{
							sign_buffer[size_buffer] = 1;
						}
						else if (size_numb != 0)
						{
							size_numb--;
							numbs_buffer[size_buffer]/=10;
							if ((size_buffer == 0) && (size_numb == 0)) space_allow_flag = false;
						}
					}
					else if (key_code == KEY_ASTERISK) //Space
					{
						if ((size_buffer < 7))
						{
							if (space_allow_flag == true)
							{
								LCD_WRITE(&LCD1, 0x20, true);
								space_allow_flag = false;
								size_buffer++;
								size_numb = 0;
							}
							else if (sign_buffer[size_buffer] != -1)
							{
								LCD_WRITE(&LCD1, 0x2D, true);
								sign_buffer[size_buffer] = -1;
							}
						}
					}
					else if (size_numb < 3)
					{
						numbs_buffer[size_buffer] = numbs_buffer[size_buffer] * (size_numb++ > 0 ? 10 : 1) + i;
						if ((sign_buffer[size_buffer] == 1) && (numbs_buffer[size_buffer] > 127))
						{
							if (numbs_buffer[size_buffer] / 100 != 1)
							{
								LCD_backspace(&LCD1);
								LCD_backspace(&LCD1);
								numbs_buffer[size_buffer] = 127;
								LCD_WRITE(&LCD1, numbs_buffer[size_buffer] / 100 + 0x30, true);
							}
							else if (numbs_buffer[size_buffer] / 10 % 10 != 2)
							{
								LCD_backspace(&LCD1);
								numbs_buffer[size_buffer] = 127;
							}
							LCD_WRITE(&LCD1, numbs_buffer[size_buffer] / 10 % 10 + 0x30, true);
						}
						else if ((sign_buffer[size_buffer] == -1) && (numbs_buffer[size_buffer] > 128))
						{
							if (numbs_buffer[size_buffer] / 100 != 1)
							{
								LCD_backspace(&LCD1);
								LCD_backspace(&LCD1);
								numbs_buffer[size_buffer] = 128;
								LCD_WRITE(&LCD1, numbs_buffer[size_buffer] / 100 + 0x30, true);
							}
							else if (numbs_buffer[size_buffer] / 10 % 10 != 2)
							{
								LCD_backspace(&LCD1);
								numbs_buffer[size_buffer] = 128;
							}
							LCD_WRITE(&LCD1, numbs_buffer[size_buffer] / 10 % 10 + 0x30, true);
						}
						if (LCD1.current_line_buffer != LCD1.current_select_line)
						{
							LCD1.current_select_line = LCD1.current_line_buffer;
							LCD_rewritingline(&LCD1);
						}
						LCD_WRITE(&LCD1, numbs_buffer[size_buffer] % 10 + 0x30, true);
						space_allow_flag = true;
					}
					DELAY(250000);
					break;
				}
			}
			key_code = -1;
		}
	}
}