#ifndef __IT_H
#define __IT_H

void NMI_Handler(void);
void HardFault_Handler(void);
void SysTick_Handler(void);

void TIM2_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);
void DMA1_Channel4_5_6_7_IRQHandler(void);

#endif /* __IT_H */
