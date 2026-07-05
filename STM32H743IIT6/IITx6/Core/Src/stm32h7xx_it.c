#include "main.h"
#include "stm32h7xx_it.h"

extern DCMI_HandleTypeDef  DCMI_Handle;
extern DMA_HandleTypeDef   DMA_Handle_dcmi;

void NMI_Handler(void) {}
void HardFault_Handler(void) { while(1) {} }
void MemManage_Handler(void) { while(1) {} }
void BusFault_Handler(void) { while(1) {} }
void UsageFault_Handler(void) { while(1) {} }
void SVC_Handler(void) {}
void DebugMon_Handler(void) {}
void PendSV_Handler(void) {}
void SysTick_Handler(void) { HAL_IncTick(); }

void DMA1_Stream0_IRQHandler(void) { HAL_DMA_IRQHandler(DCMI_Handle.DMA_Handle); }
void DMA2_Stream1_IRQHandler(void) { HAL_DMA_IRQHandler(&DMA_Handle_dcmi); }
void DCMI_IRQHandler(void) { HAL_DCMI_IRQHandler(&DCMI_Handle); }
void USART1_IRQHandler(void) { HAL_UART_IRQHandler(&huart1); }
