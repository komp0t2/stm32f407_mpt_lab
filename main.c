#include "GPIO_Library.h"
#include "stm32f407xx.h"
void init_pin();
int LCD_bufferline[10][16];
int LCD_line	   = 0;
int LCD_lenghtline = 0;
void LCD_nextline()
{
	if (LCD_line < 1)
	{
		for (int i = 0; i < 24; i++) LCD_COMMAND(0x14);
		LCD_line++;
	}
}
void LCD_prevline()
{
	if (LCD_line >= 1)
	{
		for (int i = 0; i < 24; i++) LCD_COMMAND(0x10);
		LCD_line--;
	}
}
void transformation(uint16_t *buffer)
{
	LCD_COMMAND(0x1);
	for (int i = 0; i < 8; i++)
	{
		LCD_WRITE(buffer[i] * 2 + 128);
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
	uint16_t numbs_buffer[8] = {0};
	//

	int numbs_size	= 0;
	int size_buffer = 0;

	DISPLAY_ON();
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
						LCD_COMMAND(0x1);
						numbs_size	   = 0;
						size_buffer	   = 0;
						LCD_lenghtline = 0;
						LCD_line	   = 0;
					}
					else if (key_code == KEY_A) //FUNC
					{
						LCD_WRITE(LCD_symb[i]);
						//if (size_buffer == 8)
						//	transformation(numbs_buffer);
					}
					else if (key_code == KEY_NUMBER) //BackspaceLCD
					{
						if (size_buffer > 0)
						{
							if (LCD_lenghtline <= 0)
							{
								LCD_prevline();
								LCD_lenghtline = 16;
							}
							else
								LCD_lenghtline--;
							LCD_backspace();
							size_buffer--;
							numbs_buffer[numbs_size] /= 10;
						}
						else if (numbs_size > 0)
						{
							if (LCD_lenghtline <= 0)
							{
								LCD_prevline();
								LCD_lenghtline = 16;
							}
							else
								LCD_lenghtline--;
							LCD_backspace();
							numbs_size--;
							int bkspbuffer = numbs_buffer[numbs_size];
							while (bkspbuffer > 0)
							{
								bkspbuffer /= 10;
								size_buffer++;
							}
						}
					}
					else if (numbs_size < 8)
					{
						if (key_code == KEY_ASTERISK) //Space
						{
							LCD_WRITE(0x20);
							numbs_size++;
							size_buffer = 0;
							LCD_lenghtline++;
						}
						else
						{

							if (size_buffer < 3) //Input numbs
							{
								numbs_buffer[numbs_size] = i + numbs_buffer[numbs_size] * (size_buffer <= 0 ? 0 : 10);
								size_buffer++;
								LCD_lenghtline++;
								if (numbs_buffer[numbs_size] > 127) //max numb 128
								{
									numbs_buffer[numbs_size] = 127;
									if (LCD_lenghtline < 1)
									{
										LCD_backspace();
										LCD_lenghtline--;
										LCD_prevline();
										LCD_lenghtline=15;
										LCD_backspace();
										LCD_lenghtline--;
										if (LCD_lenghtline < 14)
											{
												LCD_WRITE(LCD_symb[1]);
												LCD_WRITE(LCD_symb[2]);
												LCD_nextline();
												LCD_WRITE(LCD_symb[7]);
											}
										else if (LCD_lenghtline < 15)
										{
											LCD_WRITE(LCD_symb[1]);
											LCD_nextline();
											LCD_WRITE(LCD_symb[2]);
											LCD_WRITE(LCD_symb[7]);
										}
									}
									else
									{
										LCD_backspace();
										LCD_backspace();
										LCD_WRITE(LCD_symb[1]);
										LCD_WRITE(LCD_symb[2]);
										LCD_WRITE(LCD_symb[7]);
									}
								}
								else
								{
									LCD_WRITE(LCD_symb[i]);
									LCD_bufferline[LCD_line][LCD_lenghtline] = LCD_symb[i];
								}

								if (LCD_lenghtline >= 16)
								{
									LCD_nextline();
									LCD_lenghtline = 0;
								}
							}
						}
					}
					DELAY(250000);
					break;
				}
			}
			key_code = -1;
		}
	}
}