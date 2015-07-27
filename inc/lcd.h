/* lcd.h
 *
 *  Created on: 22.07.2015.
 *      Author: ichiro
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CNC_LCD_H
#define CNC_LCD_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "delay.h"
#include "i2c.h"
/* Exported constants --------------------------------------------------------*/
// commands
#define LCD_CLEARDISPLAY						0x01
#define LCD_RETURNHOME 							0x02
#define LCD_ENTRYMODESET 						0x04
#define LCD_DISPLAYCONTROL 						0x08
#define LCD_CURSORSHIFT 						0x10
#define LCD_FUNCTIONSET 						0x20
#define LCD_SETCGRAMADDR 						0x40
#define LCD_SETDDRAMADDR 						0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 							0x00
#define LCD_ENTRYLEFT 							0x02
#define LCD_ENTRYSHIFTINCREMENT 				0x01
#define LCD_ENTRYSHIFTDECREMENT 				0x00

// flags for display on/off control
#define LCD_DISPLAYON 							0x04
#define LCD_DISPLAYOFF 							0x00
#define LCD_CURSORON 							0x02
#define LCD_CURSOROFF 							0x00
#define LCD_BLINKON 							0x01
#define LCD_BLINKOFF 							0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 						0x08
#define LCD_CURSORMOVE 							0x00
#define LCD_MOVERIGHT 							0x04
#define LCD_MOVELEFT 							0x00

// flags for function set
#define LCD_8BITMODE 							0x10
#define LCD_4BITMODE 							0x00
#define LCD_2LINE 								0x08
#define LCD_1LINE 								0x00
#define LCD_5x10DOTS 							0x04
#define LCD_5x8DOTS 							0x00

// flags for backlight control
#define LCD_BACKLIGHT 							0x08
#define LCD_NOBACKLIGHT 						0x00

#define En 										0x04  // Enable bit
#define Rw 										0x02  // Read/Write bit
#define Rs 										0x01  // Register select bit
// 2004 display parameters
#define ADDRESS									0x27
#define COLS									20
#define ROWS									4
#define BLANK_ROW								((uint8_t *)"                    ")
#define ROW_1									0
#define ROW_2									1
#define ROW_3									2
#define ROW_4									3
/* Exported types ------------------------------------------------------------*/
typedef struct {
	uint8_t addr;
	uint8_t displayfunction;
	uint8_t displaycontrol;
	uint8_t displaymode;
	uint8_t numlines;
	uint8_t cols;
	uint8_t rows;
	uint8_t backlightval;
} lcdi2c_t;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void lcd_conf(void);

void lcd_putch(uint8_t value);
void lcd_puts(uint8_t *str);
void lcd_init(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
void lcd_begin(uint8_t rows); //, uint8_t charsize = LCD_5x8DOTS );
void lcd_clear();
void lcd_home();
void lcd_no_display();
void lcd_display();
void lcd_no_blink();
void lcd_blink();
void lcd_no_cursor();
void lcd_cursor();
void lcd_scroll_left();
void lcd_scroll_right();
void lcd_left_right();
void lcd_right_left();
void lcd_no_backlight();
void lcd_backlight();
void lcd_autoscroll();
void lcd_no_autoscroll();
void lcd_create_char(uint8_t location, uint8_t charmap[]);
void lcd_set_cursor(uint8_t col, uint8_t row);
void lcd_command(uint8_t value);

// compatibility API function aliases
void lcd_blink_on();
void lcd_blink_off();
void lcd_cursor_on();
void lcd_cursor_off();
void lcd_set_backlight(uint8_t new_val);
void lcd_load_custom_character(uint8_t char_num, uint8_t *rows);

void lcd_send(uint8_t, uint8_t);
void lcd_write_4bits(uint8_t);
void lcd_expander_write(uint8_t);
void lcd_pulse_enable(uint8_t);

// Functions for 2004 display.
void lcd_conf(void);
void lcd_puts_row(uint8_t *str, uint8_t row);
void lcd_clear_row(uint8_t row);
/* Exported variables --------------------------------------------------------*/

#endif /* CNC_LCD_H */
