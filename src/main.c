#include "main.h"

__IO uint32_t tim5_period;

void tim_conf(void);

void timer_service(void)
{
	uint8_t i;

	for (i=0; i<MAX_TIMERS; i++) {
		if (timer_queue[i].task == NULL) {
			continue;
		}
		if (timer_queue[i].ticks_cnt) {
			timer_queue[i].ticks_cnt--;
		} else {
			(timer_queue[i].task)();
			timer_queue[i].ticks_cnt = timer_queue[i].ticks;
		}
	}
}

void set_timer_task(task_ptr_t task, ticks_t ticks)
{
	uint8_t i;

	for (i=0; i<MAX_TIMERS; i++) {
		if (timer_queue[i].task == NULL) {

			timer_queue[i].task = task;
			timer_queue[i].ticks = ticks;
			timer_queue[i].ticks_cnt = ticks;

			return;
		}
	}
}

void timer_conf(void)
{
	uint8_t i;

	for (i=0; i<MAX_TIMERS; i++) {
		timer_queue[i].task = NULL;
		timer_queue[i].ticks = 0;
		timer_queue[i].ticks_cnt = 0;
	}

	// Initialize SysTick timer with 1ms period.
	if (SysTick_Config(SystemCoreClock / 1000)) {
		while (1)
			;
	}
}

void print_revs(void)
{
	uint8_t buff[20];

	sprintf((char*) buff, "%" PRIu32, revs_num);
//	lcd_clear_row(ROW_2);
	lcd_puts_row(buff, ROW_2);
}

void print_enc_pos(void)
{
	uint8_t buff[20];

	if (enc_pos != TIM3->CNT) {
		sprintf((char*) buff, "%" PRIu32, (TIM3->CNT >> 1));
		lcd_clear_row(ROW_1);
		lcd_puts_row(buff, ROW_1);

		enc_pos = TIM3->CNT;
	}
}

int main(void)
{
	tim_conf();
    usart_conf();
    lcd_conf();
    encoder_conf();
    timer_conf();

    set_timer_task(print_revs, 100);
    set_timer_task( print_enc_pos, 10);

    STM_EVAL_LEDInit(LED3);
//  STM_EVAL_LEDInit(LED4);
//  STM_EVAL_LEDInit(LED5);
//  STM_EVAL_LEDInit(LED6);

    printf("\n>>> ");
    fflush(stdout);

	while (1) {

		if (cmd_get_state(&cmd) == READY) {
			uint32_t res;

			if (sscanf(cmd.text, "%lu", &res) == 1) {
				// Maybe I need to disable the interrupt from timer here...
				TIM_SetCounter(TIM5, 1);
				TIM_SetAutoreload(TIM5, res);
				printf("You enter: %s", cmd.text);
//				fprintf(stderr, "You enter: %s", cmd.text);
			} else {
				printf("You enter something wrong... ");
//				fprintf(stderr, "You enter something wrong... ");
			}

			printf("\n>>> ");
			fflush(stdout);

			cmd_set_state(&cmd, NOT_READY);
        }
    }
}

//void gpio_conf(void)
//{
////	GPIO_InitTypeDef  GPIO_InitStructure;
////
////	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
////
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
////	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
////
////	GPIO_Init(GPIOC, &GPIO_InitStructure);
//
//	 GPIO_InitTypeDef GPIO_InitStruct;
//
//	/* Clock for GPIOD */
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//
//	/* Alternating functions for pins */
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
////	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM5);
////	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM5);
////	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM5);
//
//	/* Set pins */
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStruct);
//}

void tim_conf(void)
{
//	/* Enable clock for TIM4 */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
//	/*
//	 TIM4 is connected to APB1 bus, which has on F407 device 42MHz clock
//	 But, timer has internal PLL, which double this frequency for timer, up to 84MHz
//	 Remember: Not each timer is connected to APB1, there are also timers connected
//	 on APB2, which works at 84MHz by default, and internal PLL increase
//	 this to up to 168MHz
//
//	 Set timer prescaller
//	 Timer count frequency is set with
//
//	 timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1)
//
//	 In our case, we want a max frequency for timer, so we set prescaller to 0
//	 And our timer will have tick frequency
//
//	 timer_tick_frequency = 84000000 / (0 + 1) = 84000000
//	 */
//	TIM_BaseStruct.TIM_Prescaler = 0;
//	/* Count up */
//	TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
//	/*
//	 Set timer period when it have reset
//	 First you have to know max value for timer
//	 In our case it is 16bit = 65535
//	 To get your frequency for PWM, equation is simple
//
//	 PWM_frequency = timer_tick_frequency / (TIM_Period + 1)
//
//	 If you know your PWM frequency you want to have timer period set correct
//
//	 TIM_Period = timer_tick_frequency / PWM_frequency - 1
//
//	 In our case, for 10Khz PWM_frequency, set Period to
//
//	 TIM_Period = 84000000 / 10000 - 1 = 8399
//
//	 If you get TIM_Period larger than max timer value (in our case 65535),
//	 you have to choose larger prescaler and slow down timer tick frequency
//	 */
//	TIM_BaseStruct.TIM_Period = frequency; /* 10kHz PWM */
//	TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_BaseStruct.TIM_RepetitionCounter = 0;
//
//	/* Initialize TIM4 */
//	TIM_TimeBaseInit(TIM5, &TIM_BaseStruct);
//
//	/* Start count on TIM4 */
//	TIM_Cmd(TIM5, ENABLE);

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
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
	TIM_TimeBaseStructure.TIM_Period = 41999;
	TIM_TimeBaseStructure.TIM_Prescaler = 0; // 1MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	/* TIM IT enable */
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	/* TIM5 enable counter */
	TIM_Cmd(TIM5, ENABLE);
}

//void pwm_conf(void)
//{
	/* Common settings */

	/* PWM mode 2 = Clear on compare match */
	/* PWM mode 1 = Set on compare match */
//	TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
//	TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;

	/*
	 To get proper duty cycle, you have simple equation

	 pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 - 1

	 where DutyCycle is in percent, between 0 and 100%

	 25% duty cycle:     pulse_length = ((8399 + 1) * 25) / 100 - 1 = 2099
	 50% duty cycle:     pulse_length = ((8399 + 1) * 50) / 100 - 1 = 4199
	 75% duty cycle:     pulse_length = ((8399 + 1) * 75) / 100 - 1 = 6299
	 100% duty cycle:    pulse_length = ((8399 + 1) * 100) / 100 - 1 = 8399

	 Remember: if pulse_length is larger than TIM_Period, you will have output
	 HIGH all the time
	*/
//	TIM_OCStruct.TIM_Pulse = 2099; /* 25% duty cycle */
//	TIM_OC1Init(TIM4, &TIM_OCStruct);
//	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
//
//	TIM_OCStruct.TIM_Pulse = ((frequency + 1) * 50) / 100 - 1; /* 50% duty cycle */
//	TIM_OC1Init(TIM5, &TIM_OCStruct);
//	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

//	TIM_OCStruct.TIM_Pulse = 6299; /* 75% duty cycle */
//	TIM_OC3Init(TIM4, &TIM_OCStruct);
//	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
//
//	TIM_OCStruct.TIM_Pulse = 8399; /* 100% duty cycle */
//	TIM_OC4Init(TIM4, &TIM_OCStruct);
//	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
//}

