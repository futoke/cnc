/*
 * lcd.c
 *
 *  Created on: 22.08.2015.
 *      Author: ichiro
 */

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
lcdi2c_t lcdi2c;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set:
//    DL = 1; 8-bit interface data
//    N = 0; 1-line display
//    F = 0; 5x8 dot character font
// 3. Display on/off control:
//    D = 0; Display off
//    C = 0; Cursor off
//    B = 0; Blinking off
// 4. Entry mode set:
//    I/D = 1; Increment by 1
//    S = 0; No shift
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal constructor is called).


void lcd_putch(uint8_t value)
{
	lcd_send(value, Rs);
}

void lcd_puts(uint8_t *str)
{
  while (*str) {
	  lcd_putch(*str++);
  }
}

void lcd_init(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows)
{
	lcdi2c.addr = lcd_addr;
	lcdi2c.cols = lcd_cols;
	lcdi2c.rows = lcd_rows;
	lcdi2c.backlightval = LCD_NOBACKLIGHT;

	i2c_conf();
	lcdi2c.displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	lcd_begin(lcd_rows);
}

void lcd_begin(uint8_t lines) //, uint8_t dotsize)
{
	if (lines > 1) {
		lcdi2c.displayfunction |= LCD_2LINE;
	}
	lcdi2c.numlines = lines;

	// for some 1 line displays you can select a 10 pixel high font
	/*	if ((dotsize != 0) && (lines == 1)) {
	 _displayfunction |= LCD_5x10DOTS;
	 }*/

	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	delay_ms(50);

	// Now we pull both RS and R/W low to begin commands
	// reset expanderand turn backlight off (Bit 8 = 1)
	lcd_expander_write(lcdi2c.backlightval);
	delay_ms(1000);

	// put the LCD into 4 bit mode
	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46

	// we start in 8bit mode, try to set 4 bit mode
	lcd_write_4bits(0x03 << 4);
	delay_us(4500); // wait min 4.1ms

	// second try
	lcd_write_4bits(0x03 << 4);
	delay_us(4500); // wait min 4.1ms

	// third go!
	lcd_write_4bits(0x03 << 4);
	delay_us(150);

	// finally, set to 4-bit interface
	lcd_write_4bits(0x02 << 4);

	// set # lines, font size, etc.
	lcd_command(LCD_FUNCTIONSET | lcdi2c.displayfunction);

	// turn the display on with no cursor or blinking default
	lcdi2c.displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	lcd_display();

	// clear it off
	lcd_clear();

	// Initialize to default text direction (for roman languages)
	lcdi2c.displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

	// set the entry mode
	lcd_command(LCD_ENTRYMODESET | lcdi2c.displaymode);

	lcd_home();
}

/******************************************************************************/
/*                   High level commands for user	                          */
/******************************************************************************/

void lcd_clear()
{	// clear display, set cursor position to zero
	lcd_command(LCD_CLEARDISPLAY);
	delay_us(3000);  // this command takes a long time!
}

void lcd_home()
{
	lcd_command(LCD_RETURNHOME);  // set cursor position to zero
	delay_us(3000);  // this command takes a long time!
}

void lcd_set_cursor(uint8_t col, uint8_t row)
{
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if (row > lcdi2c.numlines) {
		row = lcdi2c.numlines - 1;    // we count rows starting w/0
	}
	lcd_command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void lcd_no_display()
{
	lcdi2c.displaycontrol &= ~LCD_DISPLAYON;
	lcd_command(LCD_DISPLAYCONTROL | lcdi2c.displaycontrol);
}

void lcd_display()
{
	lcdi2c.displaycontrol |= LCD_DISPLAYON;
	lcd_command(LCD_DISPLAYCONTROL | lcdi2c.displaycontrol);
}

// Turns the underline cursor on/off
void lcd_no_cursor()
{
	lcdi2c.displaycontrol &= ~LCD_CURSORON;
	lcd_command(LCD_DISPLAYCONTROL | lcdi2c.displaycontrol);
}

void lcd_cursor()
{
	lcdi2c.displaycontrol |= LCD_CURSORON;
	lcd_command(LCD_DISPLAYCONTROL | lcdi2c.displaycontrol);
}

// Turn on and off the blinking cursor
void lcd_no_blink()
{
	lcdi2c.displaycontrol &= ~LCD_BLINKON;
	lcd_command(LCD_DISPLAYCONTROL | lcdi2c.displaycontrol);
}

void lcd_blink()
{
	lcdi2c.displaycontrol |= LCD_BLINKON;
	lcd_command(LCD_DISPLAYCONTROL | lcdi2c.displaycontrol);
}

void lcd_scroll_left(void)
{
	lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void lcd_scroll_right(void)
{
	lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void lcd_left_right(void)
{
	lcdi2c.displaymode |= LCD_ENTRYLEFT;
	lcd_command(LCD_ENTRYMODESET | lcdi2c.displaymode);
}

// This is for text that flows Right to Left
void lcd_right_left(void)
{
	lcdi2c.displaymode &= ~LCD_ENTRYLEFT;
	lcd_command(LCD_ENTRYMODESET | lcdi2c.displaymode);
}

// This will 'right justify' text from the cursor
void lcd_autoscroll(void)
{
	lcdi2c.displaymode |= LCD_ENTRYSHIFTINCREMENT;
	lcd_command(LCD_ENTRYMODESET | lcdi2c.displaymode);
}

// This will 'left justify' text from the cursor
void lcd_no_autoscroll(void) {
	lcdi2c.displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	lcd_command(LCD_ENTRYMODESET | lcdi2c.displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void lcd_create_char(uint8_t location, uint8_t charmap[])
{
	location &= 0x7; // we only have 8 locations 0-7
	lcd_command(LCD_SETCGRAMADDR | (location << 3));
	for (int i = 0; i < 8; i++) {
		lcd_putch(charmap[i]);
	}
}

// Turn the (optional) backlight off/on
void lcd_no_backlight(void)
{
	lcdi2c.backlightval = LCD_NOBACKLIGHT;
	lcd_expander_write(0);
}

void lcd_backlight(void)
{
	lcdi2c.backlightval = LCD_BACKLIGHT;
	lcd_expander_write(0);
}


/******************************************************************************/
/*                   Mid level commands, for sending data or cmds             */
/******************************************************************************/


void lcd_command(uint8_t value)
{
	lcd_send(value, 0);
}

/******************************************************************************/
/*                           Low level data pushing commands                  */
/******************************************************************************/

// write either command or data
void lcd_send(uint8_t value, uint8_t mode)
{
	uint8_t highnib = value & 0xF0;
	uint8_t lownib = (value << 4) & 0xF0;
	lcd_write_4bits((highnib) | mode);
	lcd_write_4bits((lownib) | mode);
}

void lcd_write_4bits(uint8_t value)
{
	lcd_expander_write(value);
	lcd_pulse_enable(value);
}

void lcd_expander_write(uint8_t data)
{
	i2c_start_trans(I2C1, I2C_Direction_Transmitter, lcdi2c.addr);
	i2c_write_byte(I2C1, (int) (data) | lcdi2c.backlightval);
	I2C_GenerateSTOP(I2C1, ENABLE);
}

void lcd_pulse_enable(uint8_t data)
{
	lcd_expander_write(data | En); // En high
	delay_us(1); // enable pulse must be > 450ns

	lcd_expander_write(data & ~En); // En low
	delay_us(50); // commands need > 37us to settle
}

/******************************************************************************/
/*                               Alias functions                              */
/******************************************************************************/

void lcd_cursor_on()
{
	lcd_cursor();
}

void lcd_cursor_off()
{
	lcd_no_cursor();
}

void lcd_blink_on()
{
	lcd_blink();
}

void lcd_blink_off()
{
	lcd_no_blink();
}

void lcd_load_custom_character(uint8_t char_num, uint8_t *rows)
{
	lcd_create_char(char_num, rows);
}

void lcd_set_backlight(uint8_t new_val)
{
	if (new_val) {
		lcd_backlight(); // turn backlight on
	} else {
		lcd_no_backlight(); // turn backlight off
	}
}

/******************************************************************************/
/*                         Functions for 2004 display                         */
/******************************************************************************/

void lcd_conf(void)
{
	lcd_init(ADDRESS, COLS, ROWS);
	lcd_backlight();
}

void lcd_puts_row(uint8_t *str, uint8_t row)
{
	lcd_set_cursor(0, row);
	lcd_puts(str);
}

void lcd_clear_row(uint8_t row)
{
	lcd_puts_row(BLANK_ROW, row);
}
