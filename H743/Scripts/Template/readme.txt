实验器材:
	阿波罗STM32H7开发板 
	
实验目的:
	本实验为新建工程实验，仅供大家新建工程时参考。
	新建工程详细步骤，请看《STM32H7开发指南-HAL库版本》第3.3节。
	
硬件资源:
	1,串口1(波特率:115200,PA9/PA10连接在板载USB转串口芯片CH340上面)
	
实验现象:
	本实验下载后，DS0和DS1闪烁。 

工程文件来源：

①HAL库文件                                                                 ->   \STM32Cube_FW_H7_V1.2.0\Drivers\STM32H7xx_HAL_Driver
②startup_stm32h743xx.s                                                     ->   \STM32Cube_FW_H7_V1.2.0\Drivers\CMSIS\Device\ST\STM32H7xx\Source\Templates\arm
③cmsis_armcc.h，cmsis_armclang.h，cmsis_compiler.h，core_cm7.h             ->   \STM32Cube_FW_H7_V1.2.0\Drivers\CMSIS\Include

④stm32h7xx.h，system_stm32h7xx.h和stm32h743xx.h                            ->   \STM32Cube_FW_H7_V1.2.0\Drivers\CMSIS\Device\ST\STM32H7xx\Include

⑤stm32h7xx_it.h，stm32h7xx_hal_conf.h 和main.h                             ->   \STM32Cube_FW_H7_V1.2.0\Projects\STM32H743I_EVAL\Templates\Inc
⑥system_stm32h7xx.c，stm32h7xx_it.c, stm32h7xx_hal_msp.c 和main.c          ->   \STM32Cube_FW_H7_V1.2.0\Projects\STM32H743I_EVAL\Templates\Src

SYSTEM文件夹，任何一个HAL库实验工程中有
	
注意事项:
	无.


					正点原子@ALIENTEK
					2018-6-22
					广州市星翼电子科技有限公司
					电话：020-38271790
					传真：020-36773971
					购买：http://openedv.taobao.com
					http://eboard.taobao.com
					公司网站：www.alientek.com
					技术论坛：www.openedv.com