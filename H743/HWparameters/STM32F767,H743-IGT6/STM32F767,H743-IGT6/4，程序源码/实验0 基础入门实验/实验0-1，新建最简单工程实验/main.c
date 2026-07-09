/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-07-19
 * @brief       最精简STM32工程, 除了启动文件(.s文件), 未使用任何库文件
 *              该代码实现功能：通过PB1控制LED0闪烁
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 阿波罗 F767开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20220719
 * 第一次发布
 *
 ****************************************************************************************************
 */


/* 总线基地址定义 */
#define PERIPH_BASE         0x40000000UL                          /* 外设基地址 */

#define APB1PERIPH_BASE   PERIPH_BASE                             /* APB1总线基地址 */
#define AHB1PERIPH_BASE  (PERIPH_BASE + 0x00020000UL)             /* AHB1总线基地址 */

/* 外设基地址定义 */
#define RCC_BASE            (AHB1PERIPH_BASE + 0x3800UL)          /* RCC基地址 */
#define GPIOB_BASE          (AHB1PERIPH_BASE + 0x0400UL)          /* GPIOB基地址 */


/* 外设相关寄存器映射(定义) */
#define RCC_AHB1ENR         *(volatile unsigned int *)(RCC_BASE + 0x30)     /* RCC_AHB1ENR寄存器映射 */

#define GPIOB_MODER         *(volatile unsigned int *)(GPIOB_BASE + 0x00)   /* GPIOB_MODER寄存器映射 */
#define GPIOB_OTYPER        *(volatile unsigned int *)(GPIOB_BASE + 0x04)   /* GPIOB_OTYPER寄存器映射 */
#define GPIOB_OSPEEDR       *(volatile unsigned int *)(GPIOB_BASE + 0x08)   /* GPIOB_OSPEEDR寄存器映射 */
#define GPIOB_PUPDR         *(volatile unsigned int *)(GPIOB_BASE + 0x0C)   /* GPIOB_PUPDR寄存器映射 */
#define GPIOB_IDR           *(volatile unsigned int *)(GPIOB_BASE + 0x10)   /* GPIOB_IDR寄存器映射 */
#define GPIOB_ODR           *(volatile unsigned int *)(GPIOB_BASE + 0x14)   /* GPIOB_ODR寄存器映射 */


/* 延时函数 */
static void delay_x(volatile unsigned  long int t)
{
    while(t--);
}

/* main函数 */
int main(void)
{
    /* 未执行任何PLL时钟配置, 默认使用HSI(16M)工作, 相当于工作在主频16Mhz频率下 */

    RCC_AHB1ENR |= 1 << 1;           /* GPIOB 时钟使能 */

    GPIOB_MODER &= ~(0X03UL << 2);   /* MODER1[1:0], 清零 */
    GPIOB_MODER |= 0X01UL << 2;      /* MODER1[1:0]=1, PB1输出模式 */
    GPIOB_OTYPER &= ~(0X01UL << 1);  /* OT1, 清零, 推挽输出 */
    GPIOB_OSPEEDR &= ~(0X03UL << 2); /* OSPEEDR1[1:0], 清零 */
    GPIOB_OSPEEDR |= 0X01UL << 2;    /* OSPEEDR1[1:0]=1, 高速 */
    GPIOB_PUPDR &= ~(0X03UL << 2);   /* PUPDR1[1:0], 清零 */
    GPIOB_PUPDR |= 0X01UL << 2;      /* PUPDR1[1:0]=1, 上拉 */
    
    while(1)
    {
        GPIOB_ODR |= 1 << 1;         /* PB1 = 1, LED0灭 */
        delay_x(500000);             /* 延时一定时间 */
        GPIOB_ODR &= ~(1UL << 1);    /* PB1 = 0, LED0亮 */
        delay_x(500000);             /* 延时一定时间 */
    }
}


