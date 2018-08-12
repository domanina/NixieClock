#include "stm32f30x.h"

#define F_CPU 		72000000UL	// Тактовая у нас 72МГЦ
#define TimerTick  	F_CPU/1000-1	// Нам нужен килогерц


void Delay( uint32_t Val)
{
	for( ; Val!=0; Val--)
	{
		__nop();
	}
}



void delay_ms(uint16_t value)
{
	TIM3->ARR = value*2;
	TIM3->CNT = 0;
	TIM3->CR1 |= TIM_CR1_CEN;
	while((TIM3->SR & TIM_SR_UIF)==0){}
	TIM3->SR &= ~TIM_SR_UIF;	
}



void InitGPIO(void)
{
	RCC->AHBENR	|= RCC_AHBENR_GPIOAEN;														//Включение тактирования портов A на шине AHB (AHB2)
	RCC->AHBENR	|= RCC_AHBENR_GPIODEN;														//Включение тактирования портов D на шине AHB (AHB2)
	RCC->AHBENR	|= RCC_AHBENR_GPIOEEN; 														//Включение тактирования портов Е на шине AHB (AHB2)
	
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	GPIOA->MODER &= (~GPIO_MODER_MODER0);													//Установка пина 0, порта A (GPIOA:0) в режим входа
	GPIOA->MODER &= (~GPIO_MODER_MODER1);													//Установка пина 1, порта A (GPIOA:0) в режим входа
	GPIOA->MODER &= (~GPIO_MODER_MODER2);													//Установка пина 2, порта A (GPIOA:0) в режим входа
	GPIOA->MODER &= (~GPIO_MODER_MODER3);													//Установка пина 3, порта A (GPIOA:0) в режим входа
	
	
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_1;													//Установка пина 0, порта A (GPIOA:0) в режим pull-down (подтяжка к земле)
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR1_1;													//Установка пина 0, порта A (GPIOA:0) в режим pull-down (подтяжка к земле)
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR2_1;													//Установка пина 0, порта A (GPIOA:0) в режим pull-down (подтяжка к земле)	
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR3_1;													//Установка пина 0, порта A (GPIOA:0) в режим pull-down (подтяжка к земле)
	
	GPIOE->MODER |= GPIO_MODER_MODER15_0;													//Установка пина 15, порта E (GPIOE:15) в режим выхода
	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_15);												//Установка пина 15, порта E (GPIOE:15) в режим push-pull
	GPIOE->MODER |= GPIO_MODER_MODER14_0;													//Установка пина 14, порта E (GPIOE:14) в режим выхода
	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_14);												//Установка пина 14, порта E (GPIOE:14) в режим push-pull
	GPIOE->MODER |= GPIO_MODER_MODER13_0;													//Установка пина 13, порта E (GPIOE:13) в режим выхода
	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_13);												//Установка пина 13, порта E (GPIOE:13) в режим push-pull
	GPIOE->MODER |= GPIO_MODER_MODER12_0;													//Установка пина 12, порта E (GPIOE:12) в режим выхода
	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_12);												//Установка пина 12, порта E (GPIOE:12) в режим push-pull

	
//	GPIOD->MODER |= GPIO_MODER_MODER0_0;													//Установка пина 0, порта D (GPIOD:0) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER1_0;													//Установка пина 1, порта D (GPIOD:1) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER2_0;													//Установка пина 2, порта D (GPIOD:2) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER3_0;													//Установка пина 3, порта D (GPIOD:3) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER4_0;													//Установка пина 4, порта D (GPIOD:4) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER5_0;													//Установка пина 5, порта D (GPIOD:5) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER6_0;													//Установка пина 6, порта D (GPIOD:6) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER7_0;													//Установка пина 7, порта D (GPIOD:7) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER8_0;													//Установка пина 8, порта D (GPIOD:8) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER9_0;													//Установка пина 9, порта D (GPIOD:9) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER10_0;													//Установка пина 10, порта D (GPIOD:10) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER11_0;													//Установка пина 11, порта D (GPIOD:11) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER12_0;													//Установка пина 12, порта D (GPIOD:12) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER13_0;													//Установка пина 13, порта D (GPIOD:13) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER14_0;													//Установка пина 14, порта D (GPIOD:14) в режим выхода
//	GPIOD->MODER |= GPIO_MODER_MODER15_0;													//Установка пина 15, порта D (GPIOD:15) в режим выхода

//	GPIOE->MODER |= GPIO_MODER_MODER8_0;													//Установка пина 8, порта E (GPIOE:8) в режим выхода
//	GPIOE->MODER |= GPIO_MODER_MODER9_0;													//Установка пина 9, порта E (GPIOE:9) в режим выхода
//	GPIOE->MODER |= GPIO_MODER_MODER10_0;													//Установка пина 10, порта E (GPIOE:10) в режим выхода
//	GPIOE->MODER |= GPIO_MODER_MODER11_0;													//Установка пина 11, порта E (GPIOE:11) в режим выхода
//	GPIOE->MODER |= GPIO_MODER_MODER12_0;													//Установка пина 12, порта E (GPIOE:12) в режим выхода
//	GPIOE->MODER |= GPIO_MODER_MODER13_0;													//Установка пина 13, порта E (GPIOE:13) в режим выхода
//	GPIOE->MODER |= GPIO_MODER_MODER14_0;													//Установка пина 14, порта E (GPIOE:14) в режим выхода
//	GPIOE->MODER |= GPIO_MODER_MODER15_0;													//Установка пина 15, порта E (GPIOE:15) в режим выхода
//	
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_0);													//Установка пина 0, порта D (GPIOD:0) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_1);													//Установка пина 1, порта D (GPIOD:1) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_2);													//Установка пина 2, порта D (GPIOD:2) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_3);													//Установка пина 3, порта D (GPIOD:3) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_4);													//Установка пина 4, порта D (GPIOD:4) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_5);													//Установка пина 5, порта D (GPIOD:5) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_6);													//Установка пина 6, порта D (GPIOD:6) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_7);													//Установка пина 7, порта D (GPIOD:7) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_8);													//Установка пина 8, порта D (GPIOD:8) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_9);													//Установка пина 9, порта D (GPIOD:9) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_10);												//Установка пина 10, порта D (GPIOD:10) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_11);												//Установка пина 11, порта D (GPIOD:11) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_12);												//Установка пина 12, порта D (GPIOD:12) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_13);												//Установка пина 13, порта D (GPIOD:13) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_14);												//Установка пина 14, порта D (GPIOD:14) в режим push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_15);												//Установка пина 15, порта D (GPIOD:15) в режим push-pull
//	
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_8);													//Установка пина 8, порта E (GPIOE:8) в режим push-pull
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_9);													//Установка пина 9, порта E (GPIOE:9) в режим push-pull
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_10);												//Установка пина 10, порта E (GPIOE:10) в режим push-pull
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_11);												//Установка пина 11, порта E (GPIOE:11) в режим push-pull
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_12);												//Установка пина 12, порта E (GPIOE:12) в режим push-pull
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_13);												//Установка пина 13, порта E (GPIOE:13) в режим push-pull
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_14);												//Установка пина 14, порта E (GPIOE:14) в режим push-pull
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_15);												//Установка пина 15, порта E (GPIOE:15) в режим push-pull
//	
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR0_1;													//Установка пина 0, порта D (GPIOD:0) в режим pull-down (подтяжка к земле) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR1_1;													//Установка пина 1, порта D (GPIOD:1) в режим pull-down (подтяжка к земле) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR2_1;													//Установка пина 2, порта D (GPIOD:2) в режим pull-down (подтяжка к земле) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR3_1;													//Установка пина 3, порта D (GPIOD:3) в режим pull-down (подтяжка к земле)
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR4_1;													//Установка пина 4, порта D (GPIOD:4) в режим pull-down (подтяжка к земле) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR5_1;													//Установка пина 5, порта D (GPIOD:5) в режим pull-down (подтяжка к земле) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR6_1;													//Установка пина 6, порта D (GPIOD:6) в режим pull-down (подтяжка к земле) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR7_1;													//Установка пина 7, порта D (GPIOD:7) в режим pull-down (подтяжка к земле)	
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR8_1;													//Установка пина 8, порта D (GPIOD:8) в режим pull-down (подтяжка к земле) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR9_1;													//Установка пина 9, порта D (GPIOD:9) в режим pull-down (подтяжка к земле) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR10_1;													//Установка пина 10, порта D (GPIOD:10) в режим pull-down (подтяжка к земле) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR11_1;													//Установка пина 11, порта D (GPIOD:11) в режим pull-down (подтяжка к земле)
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR12_1;													//Установка пина 12, порта D (GPIOD:12) в режим pull-down (подтяжка к земле) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR13_1;													//Установка пина 13, порта D (GPIOD:13) в режим pull-down (подтяжка к земле) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR14_1;													//Установка пина 14, порта D (GPIOD:14) в режим pull-down (подтяжка к земле) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR15_1;													//Установка пина 15, порта D (GPIOD:15) в режим pull-down (подтяжка к земле)	
//	
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR8_1;													//Установка пина 8, порта E (GPIOE:8) в режим pull-down (подтяжка к земле) 
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR9_1;													//Установка пина 9, порта E (GPIOE:9) в режим pull-down (подтяжка к земле) 
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR10_1;													//Установка пина 10, порта E (GPIOE:10) в режим pull-down (подтяжка к земле) 
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR11_1;													//Установка пина 11, порта E (GPIOE:11) в режим pull-down (подтяжка к земле)
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR12_1;													//Установка пина 12, порта E (GPIOE:12) в режим pull-down (подтяжка к земле) 
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR13_1;													//Установка пина 13, порта E (GPIOE:13) в режим pull-down (подтяжка к земле) 
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR14_1;													//Установка пина 14, порта E (GPIOE:14) в режим pull-down (подтяжка к земле) 
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR15_1;													//Установка пина 15, порта E (GPIOE:15) в режим pull-down (подтяжка к земле)	
	

	

		
		SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;                             // Настройка прерываний на вывод
		SYSCFG->EXTICR[1] |= SYSCFG_EXTICR1_EXTI1_PA;
		SYSCFG->EXTICR[2] |= SYSCFG_EXTICR1_EXTI2_PA;
		SYSCFG->EXTICR[3] |= SYSCFG_EXTICR1_EXTI3_PA;
		
		EXTI->IMR |= EXTI_IMR_MR0;  																	//Разрешение генерации прерывания от выбранной линии:
		EXTI->IMR |= EXTI_IMR_MR1;
		EXTI->IMR |= EXTI_IMR_MR2;
		EXTI->IMR |= EXTI_IMR_MR3;
		
		EXTI->RTSR |= EXTI_RTSR_TR0;																	 //Настройка прерывания по восходящему фронту сигнала (нажатие кнопки)
		EXTI->RTSR |= EXTI_FTSR_TR1;
		EXTI->RTSR |= EXTI_FTSR_TR2;
		EXTI->RTSR |= EXTI_FTSR_TR3;
		
		//EXTI->FTSR |= EXTI_FTSR_TR0;
	//	EXTI->FTSR |= EXTI_FTSR_TR1;
		//EXTI->FTSR |= EXTI_FTSR_TR2;
		//EXTI->FTSR |= EXTI_FTSR_TR3;
		
		
		
	
//	Timer3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;							//Включение тактирования таймера TIM3
	TIM3->PSC = 36000;																	//Настройка делителя частоты 72Мгц/36000 = частота таймера 2000 Гц 
	TIM3->CR1 |= TIM_CR1_OPM;
	return;
}


void InitRTC(void)
{
	RCC->CSR |= RCC_CSR_LSION;
	while ( !(RCC->CSR & RCC_CSR_LSIRDY) ){}
	RCC->APB1ENR |= RCC_APB1ENR_PWREN; 							// Включение тактирования модуля PWR шине APB1
	PWR->CR |= PWR_CR_DBP;																				// Включение разрешения записи в регистры RTC
	RCC->BDCR |= RCC_BDCR_RTCSEL_LSI;															// Выбор источника тактирования RTC (от низкоскоростного внутреннего источника LSI(40 kHz))
	RCC->BDCR |= RCC_BDCR_RTCEN;																	// Включение тактирования RTC
	RTC->WPR = 0xCA;																							// Отключение защиты от записи в регистры RTC
  RTC->WPR = 0x53;																							// Отключение защиты от записи в регистры RTC
	RTC->ISR |= RTC_ISR_INIT;																    	// Вход в режим редактирования
  while( !(RTC->ISR & RTC_ISR_INITF) ){}; 											// Ждем подтверждения входа в режим редактирования
  RTC->PRER = (uint32_t)(99 << 16);															// Установим асинхронный предделитель на 100(99+1).
  RTC->PRER |= (uint32_t)399;																		// Установим синхронный предделитель на 400(399+1).
	RTC->ISR &= ~(RTC_ISR_INIT);																	// Выход из режима редактирования
	RTC->WPR = 0xFF;																							// Включение защиты от записи в регистры RTC
}

void InitSysTimer(void)
{
	SysTick->LOAD = TimerTick;															//Загрузка значений
	SysTick->VAL = TimerTick;																//  Обнуление значений и флагов
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |					// Функция разрешает генерацию исключений и запускает счётчик с тактированием от тактового сигнала процессора
																											// Функция возвращает 0 в случае успеха и 1 в случае ошибки. Ошибка возникает в случае выхода аргумента за допустимые пределы
                  SysTick_CTRL_TICKINT_Msk   |
                  SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void)
{
	//GPIOD->BRR = ((uint32_t)0xFFFF);						   						//Стирание в регистре вывода
	//GPIOE->BRR = ((uint32_t)0xFF00);
	//GPIOD->BSRR = (RTC->TR & (uint32_t)0xFFFF);								//Запись в регистр вывода значений из регистра TR (16 бит)
	//GPIOE->BSRR = ((RTC->TR & (uint32_t)0x3F00)>>8);

}

void EXTI0_IRQHandler(void)
{
	EXTI->PR = EXTI_PR_PR0;
	//delay_ms(10);
	//if((GPIOA->IDR & GPIO_IDR_0) != 0)
	//{	
	GPIOE->BSRR |= GPIO_BSRR_BS_15;
	//}
}

void EXTI1_IRQHandler(void)
{
	EXTI->PR = EXTI_PR_PR1;
	//delay_ms(20);
	//if((GPIOA->IDR & GPIO_IDR_1) != 0)
	//{	
	GPIOE->BSRR |= (GPIOE->ODR >> 1);
	//}
}

void EXTI2_TS_IRQHandler(void)
{
	EXTI->PR = EXTI_PR_PR2;
	//delay_ms(10);
	//if((GPIOA->IDR & GPIO_IDR_0) != 0)
	//{	
	GPIOE->BSRR |= GPIO_BSRR_BS_13;
	//}
}


void EXTI3_IRQHandler(void)
{
	EXTI->PR = EXTI_PR_PR3;
	//delay_ms(10);
	//if((GPIOA->IDR & GPIO_IDR_0) != 0)
	//{	
	GPIOE->BSRR |= GPIO_BSRR_BR_15;
	GPIOE->BSRR |= GPIO_BSRR_BR_14;
	GPIOE->BSRR |= GPIO_BSRR_BR_13;
	GPIOE->BSRR |= GPIO_BSRR_BR_12;
	//}
}

int main()
{ 
	//__enable_irq ();
	NVIC_SetPriority(EXTI0_IRQn, 15);
	NVIC_SetPriority(EXTI1_IRQn, 16);
	NVIC_SetPriority(EXTI2_TS_IRQn, 17);
	NVIC_SetPriority(EXTI3_IRQn, 18);
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_TS_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	
	InitGPIO();
	InitRTC();
	InitSysTimer();
		
	while(1)
	{
		
		
		

		
		
//		if((GPIOA->IDR & GPIO_IDR_0) != 0)
//		{
//			GPIOE->BSRR |= GPIO_BSRR_BS_15;
//		}
//		else
//		{
//			GPIOE->BSRR |= GPIO_BSRR_BR_15;
//		}


	}
	
}
