#include "stm32f30x.h"

#define F_CPU 		72000000UL	// �������� � ��� 72���
#define TimerTick  	F_CPU/1000-1	// ��� ����� ��������


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
	RCC->AHBENR	|= RCC_AHBENR_GPIOAEN;														//��������� ������������ ������ A �� ���� AHB (AHB2)
	RCC->AHBENR	|= RCC_AHBENR_GPIODEN;														//��������� ������������ ������ D �� ���� AHB (AHB2)
	RCC->AHBENR	|= RCC_AHBENR_GPIOEEN; 														//��������� ������������ ������ � �� ���� AHB (AHB2)
	
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	GPIOA->MODER &= (~GPIO_MODER_MODER0);													//��������� ���� 0, ����� A (GPIOA:0) � ����� �����
	GPIOA->MODER &= (~GPIO_MODER_MODER1);													//��������� ���� 1, ����� A (GPIOA:0) � ����� �����
	GPIOA->MODER &= (~GPIO_MODER_MODER2);													//��������� ���� 2, ����� A (GPIOA:0) � ����� �����
	GPIOA->MODER &= (~GPIO_MODER_MODER3);													//��������� ���� 3, ����� A (GPIOA:0) � ����� �����
	
	
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_1;													//��������� ���� 0, ����� A (GPIOA:0) � ����� pull-down (�������� � �����)
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR1_1;													//��������� ���� 0, ����� A (GPIOA:0) � ����� pull-down (�������� � �����)
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR2_1;													//��������� ���� 0, ����� A (GPIOA:0) � ����� pull-down (�������� � �����)	
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR3_1;													//��������� ���� 0, ����� A (GPIOA:0) � ����� pull-down (�������� � �����)
	
	GPIOE->MODER |= GPIO_MODER_MODER15_0;													//��������� ���� 15, ����� E (GPIOE:15) � ����� ������
	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_15);												//��������� ���� 15, ����� E (GPIOE:15) � ����� push-pull
	GPIOE->MODER |= GPIO_MODER_MODER14_0;													//��������� ���� 14, ����� E (GPIOE:14) � ����� ������
	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_14);												//��������� ���� 14, ����� E (GPIOE:14) � ����� push-pull
	GPIOE->MODER |= GPIO_MODER_MODER13_0;													//��������� ���� 13, ����� E (GPIOE:13) � ����� ������
	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_13);												//��������� ���� 13, ����� E (GPIOE:13) � ����� push-pull
	GPIOE->MODER |= GPIO_MODER_MODER12_0;													//��������� ���� 12, ����� E (GPIOE:12) � ����� ������
	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_12);												//��������� ���� 12, ����� E (GPIOE:12) � ����� push-pull

	
//	GPIOD->MODER |= GPIO_MODER_MODER0_0;													//��������� ���� 0, ����� D (GPIOD:0) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER1_0;													//��������� ���� 1, ����� D (GPIOD:1) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER2_0;													//��������� ���� 2, ����� D (GPIOD:2) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER3_0;													//��������� ���� 3, ����� D (GPIOD:3) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER4_0;													//��������� ���� 4, ����� D (GPIOD:4) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER5_0;													//��������� ���� 5, ����� D (GPIOD:5) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER6_0;													//��������� ���� 6, ����� D (GPIOD:6) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER7_0;													//��������� ���� 7, ����� D (GPIOD:7) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER8_0;													//��������� ���� 8, ����� D (GPIOD:8) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER9_0;													//��������� ���� 9, ����� D (GPIOD:9) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER10_0;													//��������� ���� 10, ����� D (GPIOD:10) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER11_0;													//��������� ���� 11, ����� D (GPIOD:11) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER12_0;													//��������� ���� 12, ����� D (GPIOD:12) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER13_0;													//��������� ���� 13, ����� D (GPIOD:13) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER14_0;													//��������� ���� 14, ����� D (GPIOD:14) � ����� ������
//	GPIOD->MODER |= GPIO_MODER_MODER15_0;													//��������� ���� 15, ����� D (GPIOD:15) � ����� ������

//	GPIOE->MODER |= GPIO_MODER_MODER8_0;													//��������� ���� 8, ����� E (GPIOE:8) � ����� ������
//	GPIOE->MODER |= GPIO_MODER_MODER9_0;													//��������� ���� 9, ����� E (GPIOE:9) � ����� ������
//	GPIOE->MODER |= GPIO_MODER_MODER10_0;													//��������� ���� 10, ����� E (GPIOE:10) � ����� ������
//	GPIOE->MODER |= GPIO_MODER_MODER11_0;													//��������� ���� 11, ����� E (GPIOE:11) � ����� ������
//	GPIOE->MODER |= GPIO_MODER_MODER12_0;													//��������� ���� 12, ����� E (GPIOE:12) � ����� ������
//	GPIOE->MODER |= GPIO_MODER_MODER13_0;													//��������� ���� 13, ����� E (GPIOE:13) � ����� ������
//	GPIOE->MODER |= GPIO_MODER_MODER14_0;													//��������� ���� 14, ����� E (GPIOE:14) � ����� ������
//	GPIOE->MODER |= GPIO_MODER_MODER15_0;													//��������� ���� 15, ����� E (GPIOE:15) � ����� ������
//	
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_0);													//��������� ���� 0, ����� D (GPIOD:0) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_1);													//��������� ���� 1, ����� D (GPIOD:1) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_2);													//��������� ���� 2, ����� D (GPIOD:2) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_3);													//��������� ���� 3, ����� D (GPIOD:3) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_4);													//��������� ���� 4, ����� D (GPIOD:4) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_5);													//��������� ���� 5, ����� D (GPIOD:5) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_6);													//��������� ���� 6, ����� D (GPIOD:6) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_7);													//��������� ���� 7, ����� D (GPIOD:7) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_8);													//��������� ���� 8, ����� D (GPIOD:8) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_9);													//��������� ���� 9, ����� D (GPIOD:9) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_10);												//��������� ���� 10, ����� D (GPIOD:10) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_11);												//��������� ���� 11, ����� D (GPIOD:11) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_12);												//��������� ���� 12, ����� D (GPIOD:12) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_13);												//��������� ���� 13, ����� D (GPIOD:13) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_14);												//��������� ���� 14, ����� D (GPIOD:14) � ����� push-pull
//	GPIOD->OTYPER &= (~GPIO_OTYPER_OT_15);												//��������� ���� 15, ����� D (GPIOD:15) � ����� push-pull
//	
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_8);													//��������� ���� 8, ����� E (GPIOE:8) � ����� push-pull
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_9);													//��������� ���� 9, ����� E (GPIOE:9) � ����� push-pull
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_10);												//��������� ���� 10, ����� E (GPIOE:10) � ����� push-pull
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_11);												//��������� ���� 11, ����� E (GPIOE:11) � ����� push-pull
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_12);												//��������� ���� 12, ����� E (GPIOE:12) � ����� push-pull
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_13);												//��������� ���� 13, ����� E (GPIOE:13) � ����� push-pull
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_14);												//��������� ���� 14, ����� E (GPIOE:14) � ����� push-pull
//	GPIOE->OTYPER &= (~GPIO_OTYPER_OT_15);												//��������� ���� 15, ����� E (GPIOE:15) � ����� push-pull
//	
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR0_1;													//��������� ���� 0, ����� D (GPIOD:0) � ����� pull-down (�������� � �����) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR1_1;													//��������� ���� 1, ����� D (GPIOD:1) � ����� pull-down (�������� � �����) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR2_1;													//��������� ���� 2, ����� D (GPIOD:2) � ����� pull-down (�������� � �����) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR3_1;													//��������� ���� 3, ����� D (GPIOD:3) � ����� pull-down (�������� � �����)
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR4_1;													//��������� ���� 4, ����� D (GPIOD:4) � ����� pull-down (�������� � �����) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR5_1;													//��������� ���� 5, ����� D (GPIOD:5) � ����� pull-down (�������� � �����) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR6_1;													//��������� ���� 6, ����� D (GPIOD:6) � ����� pull-down (�������� � �����) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR7_1;													//��������� ���� 7, ����� D (GPIOD:7) � ����� pull-down (�������� � �����)	
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR8_1;													//��������� ���� 8, ����� D (GPIOD:8) � ����� pull-down (�������� � �����) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR9_1;													//��������� ���� 9, ����� D (GPIOD:9) � ����� pull-down (�������� � �����) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR10_1;													//��������� ���� 10, ����� D (GPIOD:10) � ����� pull-down (�������� � �����) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR11_1;													//��������� ���� 11, ����� D (GPIOD:11) � ����� pull-down (�������� � �����)
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR12_1;													//��������� ���� 12, ����� D (GPIOD:12) � ����� pull-down (�������� � �����) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR13_1;													//��������� ���� 13, ����� D (GPIOD:13) � ����� pull-down (�������� � �����) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR14_1;													//��������� ���� 14, ����� D (GPIOD:14) � ����� pull-down (�������� � �����) 
//	GPIOD->PUPDR |= GPIO_PUPDR_PUPDR15_1;													//��������� ���� 15, ����� D (GPIOD:15) � ����� pull-down (�������� � �����)	
//	
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR8_1;													//��������� ���� 8, ����� E (GPIOE:8) � ����� pull-down (�������� � �����) 
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR9_1;													//��������� ���� 9, ����� E (GPIOE:9) � ����� pull-down (�������� � �����) 
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR10_1;													//��������� ���� 10, ����� E (GPIOE:10) � ����� pull-down (�������� � �����) 
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR11_1;													//��������� ���� 11, ����� E (GPIOE:11) � ����� pull-down (�������� � �����)
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR12_1;													//��������� ���� 12, ����� E (GPIOE:12) � ����� pull-down (�������� � �����) 
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR13_1;													//��������� ���� 13, ����� E (GPIOE:13) � ����� pull-down (�������� � �����) 
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR14_1;													//��������� ���� 14, ����� E (GPIOE:14) � ����� pull-down (�������� � �����) 
//	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR15_1;													//��������� ���� 15, ����� E (GPIOE:15) � ����� pull-down (�������� � �����)	
	

	

		
		SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;                             // ��������� ���������� �� �����
		SYSCFG->EXTICR[1] |= SYSCFG_EXTICR1_EXTI1_PA;
		SYSCFG->EXTICR[2] |= SYSCFG_EXTICR1_EXTI2_PA;
		SYSCFG->EXTICR[3] |= SYSCFG_EXTICR1_EXTI3_PA;
		
		EXTI->IMR |= EXTI_IMR_MR0;  																	//���������� ��������� ���������� �� ��������� �����:
		EXTI->IMR |= EXTI_IMR_MR1;
		EXTI->IMR |= EXTI_IMR_MR2;
		EXTI->IMR |= EXTI_IMR_MR3;
		
		EXTI->RTSR |= EXTI_RTSR_TR0;																	 //��������� ���������� �� ����������� ������ ������� (������� ������)
		EXTI->RTSR |= EXTI_FTSR_TR1;
		EXTI->RTSR |= EXTI_FTSR_TR2;
		EXTI->RTSR |= EXTI_FTSR_TR3;
		
		//EXTI->FTSR |= EXTI_FTSR_TR0;
	//	EXTI->FTSR |= EXTI_FTSR_TR1;
		//EXTI->FTSR |= EXTI_FTSR_TR2;
		//EXTI->FTSR |= EXTI_FTSR_TR3;
		
		
		
	
//	Timer3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;							//��������� ������������ ������� TIM3
	TIM3->PSC = 36000;																	//��������� �������� ������� 72���/36000 = ������� ������� 2000 �� 
	TIM3->CR1 |= TIM_CR1_OPM;
	return;
}


void InitRTC(void)
{
	RCC->CSR |= RCC_CSR_LSION;
	while ( !(RCC->CSR & RCC_CSR_LSIRDY) ){}
	RCC->APB1ENR |= RCC_APB1ENR_PWREN; 							// ��������� ������������ ������ PWR ���� APB1
	PWR->CR |= PWR_CR_DBP;																				// ��������� ���������� ������ � �������� RTC
	RCC->BDCR |= RCC_BDCR_RTCSEL_LSI;															// ����� ��������� ������������ RTC (�� ���������������� ����������� ��������� LSI(40 kHz))
	RCC->BDCR |= RCC_BDCR_RTCEN;																	// ��������� ������������ RTC
	RTC->WPR = 0xCA;																							// ���������� ������ �� ������ � �������� RTC
  RTC->WPR = 0x53;																							// ���������� ������ �� ������ � �������� RTC
	RTC->ISR |= RTC_ISR_INIT;																    	// ���� � ����� ��������������
  while( !(RTC->ISR & RTC_ISR_INITF) ){}; 											// ���� ������������� ����� � ����� ��������������
  RTC->PRER = (uint32_t)(99 << 16);															// ��������� ����������� ������������ �� 100(99+1).
  RTC->PRER |= (uint32_t)399;																		// ��������� ���������� ������������ �� 400(399+1).
	RTC->ISR &= ~(RTC_ISR_INIT);																	// ����� �� ������ ��������������
	RTC->WPR = 0xFF;																							// ��������� ������ �� ������ � �������� RTC
}

void InitSysTimer(void)
{
	SysTick->LOAD = TimerTick;															//�������� ��������
	SysTick->VAL = TimerTick;																//  ��������� �������� � ������
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |					// ������� ��������� ��������� ���������� � ��������� ������� � ������������� �� ��������� ������� ����������
																											// ������� ���������� 0 � ������ ������ � 1 � ������ ������. ������ ��������� � ������ ������ ��������� �� ���������� �������
                  SysTick_CTRL_TICKINT_Msk   |
                  SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void)
{
	//GPIOD->BRR = ((uint32_t)0xFFFF);						   						//�������� � �������� ������
	//GPIOE->BRR = ((uint32_t)0xFF00);
	//GPIOD->BSRR = (RTC->TR & (uint32_t)0xFFFF);								//������ � ������� ������ �������� �� �������� TR (16 ���)
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
