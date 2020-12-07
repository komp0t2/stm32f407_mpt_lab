#ifndef __LCD_Library_H
#define __LCD_Library_H
#include "GPIO_Library.h"
#define LCD_length 16 //Количество символов в строке
#define LCD_height 2 //Количество строк
#define LCD_bufferline 10 //Общее количество строк буфера

typedef enum
{
	LCD_ZERO	 = 0x30,
	LCD_ONE		 = 0x31,
	LCD_TWO		 = 0x32,
	LCD_THREE	 = 0x33,
	LCD_FOUR	 = 0x34,
	LCD_FIVE	 = 0x35,
	LCD_SIX		 = 0x36,
	LCD_SEVEN	 = 0x37,
	LCD_EIGHT	 = 0x38,
	LCD_NINE	 = 0x39,
	LCD_A		 = 0x41,
	LCD_B		 = 0x42,
	LCD_C		 = 0x43,
	LCD_D		 = 0x44,
	LCD_ASTERISK = 0x2A,
	LCD_NUMBER	 = 0x23,
} LCD_CODE_SYMBOL;
typedef struct
{
	int current_line;
	int current_symb;
	int current_line_buffer;
	int current_select_line;
	int buffer_line[LCD_bufferline][LCD_length];
} LCD_InitTypeDef;
void LCD_nextline(LCD_InitTypeDef *LCD);
void LCD_COMMAND(uint8_t num) //Команды управления дисплея
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
void LCD_WRITEsys(uint8_t num)
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
void LCD_WRITE(LCD_InitTypeDef *LCD, uint8_t num, bool buffer) //Запись данных в дисплей
{
	if ((LCD->current_line_buffer >= LCD_bufferline - 1) && (LCD->current_symb >= LCD_length))
	{
		return;
	}
	if (buffer == true) LCD->buffer_line[LCD->current_line_buffer][LCD->current_symb] = num;
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
	if ((LCD->current_line_buffer == LCD_bufferline - 1) && (LCD->current_symb == LCD_length - 1))
		LCD->current_symb++;
	if (LCD->current_symb >= LCD_length - 1)
	{
		LCD_nextline(LCD);
	}
	else
		LCD->current_symb++;
}
void LCD_nextline(LCD_InitTypeDef *LCD)
{
	if (LCD->current_line < 1) //next line if a current_line = 0
	{
		for (int i = 0; i < 24; i++) LCD_COMMAND(0x14);
		LCD->current_line++;
		LCD->current_line_buffer++;
		LCD->current_symb = 0;
	}
	else if (LCD->current_line_buffer >= LCD_bufferline - 1)
	{
		return;
	}
	else
	{
		LCD_COMMAND(0x1);
		LCD->current_line = 0;
		LCD->current_symb = 0;
		for (int i = 0; i < LCD_length; i++)
		{
			LCD_WRITE(LCD, LCD->buffer_line[LCD->current_line_buffer][i], true);
		}
	}
	LCD->current_select_line = LCD->current_line_buffer;
}
void LCD_Clear(LCD_InitTypeDef *LCD)
{
	LCD_COMMAND(0x1);
	LCD->current_line		 = 0;
	LCD->current_symb		 = 0;
	LCD->current_line_buffer = 0;
}
void LCD_rewritingline(LCD_InitTypeDef *LCD)
{
	int tmp_current_symb = LCD->current_symb;
	int tmp_current_line = LCD->current_line;
	LCD_COMMAND(0x1);
	LCD->current_line = 0;
	LCD->current_symb = 0;
	//
	int m = 0;
	for (int i = tmp_current_line; i >= 0; i--)
	{
		if ((tmp_current_line > 0) && (i == 1))
		{
			m = LCD_length;
			LCD->current_line_buffer--;
		}
		else
			m = tmp_current_symb;
		for (int j = 0; j < m; j++)
			LCD_WRITE(LCD, LCD->buffer_line[LCD->current_line_buffer][j], false);
	}
}
void LCD_backspace(LCD_InitTypeDef *LCD)
{
	if ((LCD->current_symb == 0) && (LCD->current_line > 0) && (LCD->current_line_buffer > 0))
	{
		if (LCD->current_line_buffer == 2)
			LCD->current_line = 1;
		else
			LCD->current_line--;
		LCD->current_line_buffer--;
		LCD->current_symb = 15;
	}
	else if ((LCD->current_symb == 0) && (LCD->current_line_buffer > 0))
	{
		LCD->current_line = 1;
		LCD->current_line_buffer--;
		LCD->current_symb = 15;
	}
	else if (LCD->current_symb > 0)
	{
		LCD->current_symb--;
	}
	if (LCD->current_line_buffer != LCD->current_select_line)
	{
		LCD->current_select_line = LCD->current_line_buffer;
		LCD_rewritingline(LCD);
	}
	else
		LCD_rewritingline(LCD);
	LCD->current_select_line = LCD->current_line_buffer;
}
void LCD_lineup(LCD_InitTypeDef *LCD)
{
	int tmp_current_line		= LCD->current_line;
	int tmp_current_symb		= LCD->current_symb;
	int tmp_current_line_buffer = LCD->current_line_buffer;
	if (LCD->current_select_line > 0)
	{
		LCD->current_line = 1;
		if (LCD->current_select_line > 1)
		{
			LCD->current_line_buffer = --LCD->current_select_line;
			LCD->current_symb		 = 15;
			LCD_rewritingline(LCD);
			LCD_WRITEsys(LCD->buffer_line[LCD->current_line_buffer][LCD->current_symb]);
		}
	}
	else
	{
		LCD->current_line_buffer = LCD->current_select_line;
		LCD_rewritingline(LCD);
	}
	LCD->current_line		 = tmp_current_line;
	LCD->current_symb		 = tmp_current_symb;
	LCD->current_line_buffer = tmp_current_line_buffer;
}
void LCD_linedown(LCD_InitTypeDef *LCD)
{
	int tmp_current_line		= LCD->current_line;
	int tmp_current_symb		= LCD->current_symb;
	int tmp_current_line_buffer = LCD->current_line_buffer;
	if (LCD->current_select_line < tmp_current_line_buffer)
	{
		LCD->current_line		 = 1;
		LCD->current_line_buffer = ++LCD->current_select_line;
		if (LCD->current_select_line != tmp_current_line_buffer) LCD->current_symb = 15;
		LCD_rewritingline(LCD);
		//LCD_WRITEsys(LCD->buffer_line[LCD->current_line_buffer][LCD->current_symb]);
	}
	LCD->current_line		 = tmp_current_line;
	LCD->current_symb		 = tmp_current_symb;
	LCD->current_line_buffer = tmp_current_line_buffer;
}
void DISPLAY_ON(LCD_InitTypeDef *LCD) //Инициализация дисплея
{
	LCD->current_line		 = 0;
	LCD->current_symb		 = 0;
	LCD->current_line_buffer = 0;
	LCD->current_select_line = 0;
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
	LCD_COMMAND(0x0F);
	delay();
}
#endif /* __LCD_Library_H */