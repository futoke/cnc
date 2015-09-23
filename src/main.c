#include "main.h"

float32_t isqrtf(float32_t num)
{
    float32_t result;
    __ASM volatile ("vsqrt.f32 %0, %1" : "=w" (result) : "w" (num) );
    return (result);
}

void print_enc_revs(void)
{
    uint8_t buff[10];
    static uint8_t init = 1;
    static uint32_t enc_revs_num_prev;
    
    if (init) {
        lcd_clear_row(ROW_2);
        lcd_puts_row((uint8_t *)"Revolutions: 0", ROW_2);
        init = 0;
    }
    
    if (enc_revs_num != enc_revs_num_prev) {
        sprintf((char*)buff, "%" PRIu32, enc_revs_num);
        lcd_set_cursor(13, ROW_2); // Shifting for "Revolutions: "
        lcd_puts(buff);
        enc_revs_num_prev = enc_revs_num;
    }
}

void print_enc_velocity(void)
{
    uint8_t buff[10];
    float velocity_rev_per_min;
    static uint8_t init = 1;
    static uint32_t enc_velocity_prev;
    
    if (init) {
        lcd_clear_row(ROW_3);
        lcd_puts_row((uint8_t *)"Velocity: 0", ROW_3);
        init = 0;
    }
    
    if (enc_velocity != enc_velocity_prev) {
        // Measuring velocity 10 times per second (100 ms interval).
        velocity_rev_per_min = ((float)enc_velocity / TICKS_PER_REV) * 600.0;
        sprintf((char*)buff, "%5.1f", velocity_rev_per_min);
        lcd_set_cursor(10, ROW_3); // Shifting for "Velocity: " (10 chars).
        lcd_puts((uint8_t*)"          "); // 10 spaces for erase.
        lcd_set_cursor(10, ROW_3);
        lcd_puts(buff);
        
        enc_velocity_prev = enc_velocity;
    }
}

void print_enc_pos(void)
{
    uint8_t buff[10];
    static uint8_t init = 1;
    static uint32_t enc_pos_prev;
    
    if (init) {
        lcd_clear_row(ROW_1);
        lcd_puts_row((uint8_t *)"Position: 0", ROW_1);
        init = 0;
    }
    
    if (enc_pos != enc_pos_prev) {
        sprintf((char*)buff, "%" PRIu32, enc_pos);
        lcd_set_cursor(10, ROW_1); // Shifting for "Position: ".
        lcd_puts((uint8_t*)"          "); // 9 spaces for erase.
        lcd_set_cursor(10, ROW_1);
        lcd_puts(buff);
        
        enc_pos_prev = enc_pos;
    }
}

void calculate_velocity(void)
{
    static uint32_t enc_ticks_prev, enc_pos_prev;
    enc_pos = (TIM3->CNT >> 1);
    
    enc_ticks += abs(enc_pos - enc_pos_prev);
    enc_velocity = enc_ticks - enc_ticks_prev;
    
    enc_pos_prev = enc_pos;
    enc_ticks_prev = enc_ticks;
    
}

void cmd_echo(void)
{
    uint8_t ch;
    
    if (!buff_empty(rx_buff)) {
        ch = buff_get(&rx_buff);
        cmd_add_ch(&cmd, ch);
        usart_putch(ch);
    }
}

void cmd_processor(void)
{
    int32_t number;
    uint8_t number_str[16];
    uint8_t prefix;
    uint8_t char_counter = 0;

    if (cmd_get_state(&cmd) == READY) {
        
//        printf(">>> ");
//        fflush(stdout);
        
        if (y_steps == 0) { // No motion.

            while (cmd.text[char_counter]) {
                if (char_counter == 0) {
                    prefix = cmd.text[char_counter];
                } else {
                    number_str[char_counter - 1] = cmd.text[char_counter];
                }
                char_counter++;
            }
            number_str[char_counter - 1] = '\0';

            if (sscanf((char*)number_str, "%" PRIi32, &number) != 1) {
                printf("You enter something wrong... ");
            } else {
                switch (prefix) {
                    case 'F':
                    case 'f':
                        if (number > 0) {
                            // Load desire period (max block speed).
                            y_period = (uint32_t)number;
                            y_curr_period = BEGIN_PERIOD;
                            // Maybe I need to disable the interrupt from timer here...
                            TIM_SetCounter(TIM5, 1);
                            TIM_SetAutoreload(TIM5, y_curr_period);
                            printf("Set feedrate: %" PRIi32 " parrots.", number);
                        } else {
                            printf("Feedrate should be positive. "
                                   "You enter: %" PRIi32".", number);
                        }
                        break;
                    case 'Y':
                    case 'y':
                        if (number > 0) { // CW.
                            STM_EVAL_LEDOn(LED5);
                        } else { // CCW.
                            STM_EVAL_LEDOff(LED5);
                        }
                        y_steps = (abs(number) << 1);
                        printf(
                            "Set Y relative position: %" PRIi32 " microsteps "
                            "(%.3f mm)", number, MICROSTEPS_TO_MM(number)
                        );
                        break;
                    default:
                        printf("Unsupported command '%c'.", (char)prefix);
                        break;
                }
            }
        } else {
            printf("Motion is not complete!");
        }

        printf("\n>>> ");
        fflush(stdout);
        
        cmd_set_state(&cmd, NOT_READY);
    }
}

int main(void)
{
    y_steps = 0; // !!!!!!!!!
    y_period = 2000;
    y_curr_period = BEGIN_PERIOD;

    tim_conf();
    usart_conf();
//    lcd_conf();
//    encoder_conf();
    interval_conf();

    STM_EVAL_LEDInit(LED3); // Step pin PD13 for Y axis.
//    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED5); // Dir pin PD14 for Y axis.
//    STM_EVAL_LEDInit(LED6);

    set_interval_task(cmd_processor, 1);
    
//    set_interval_task(print_enc_revs, 500);
//    set_interval_task(print_enc_pos, 500);
//    set_interval_task(print_enc_velocity, 100);
//
//    set_interval_task(calculate_velocity, 100);
    set_interval_task(cmd_echo, 1);

    while (1)
        ;
}

void tim_conf(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* Enable the TIM5 gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* TIM5 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = y_curr_period - 1; // !!!!!!!!!!!!!!
    TIM_TimeBaseStructure.TIM_Prescaler = 0; // 4MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
    /* TIM IT enable */
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
    /* TIM5 enable counter */
    TIM_Cmd(TIM5, ENABLE);
}
