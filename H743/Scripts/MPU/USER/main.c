#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h"
#include "key.h"
#include "mpu.h"
/************************************************
 ALIENTEK 阿波罗STM32H7开发板 实验12
 MPU(内存保护)实验-HAL库函数版
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

u8 mpudata[128] __attribute__((at(0X20002000)));//定义一个数组

int main(void)
{	 
	u8 i=0;
	u8 key;
	
	Cache_Enable();                			//打开L1-Cache
	HAL_Init();				        		//初始化HAL库
	Stm32_Clock_Init(160,5,2,4);  		    //设置时钟,400Mhz 
	delay_init(400);						//延时初始化
	uart_init(115200);						//串口初始化
	LED_Init();								//初始化LED
	KEY_Init();								//初始化按键
    printf("\r\n\r\nMPU closed!\r\n");		//提示MPU关闭    
    while(1)
    {
		key=KEY_Scan(0);
        if(key==WKUP_PRES)              //使能MPU保护数组 mpudata;
        {           
            MPU_Set_Protection( 0X20002000,//只读,禁止共用,禁止catch,允许缓冲 
                                MPU_REGION_SIZE_128B,
                                MPU_REGION_NUMBER0,
                                MPU_REGION_PRIV_RO_URO,
                                MPU_ACCESS_NOT_SHAREABLE,
                                MPU_ACCESS_NOT_CACHEABLE,
                                MPU_ACCESS_BUFFERABLE);  
            printf("MPU open!\r\n");	//提示MPU打开
        }else if(key==KEY0_PRES)        //向数组中写入数据，如果开启了MPU保护的话会进入内存访问错误！
        {
			printf("Start Writing data...\r\n");
			sprintf((char*)mpudata,"MPU test array %d",i);
			printf("Data Write finshed!\r\n");
        }else if(key==KEY1_PRES)		//从数组中读取数据，不管有没有开启MPU保护都不会进入内存访问错误！
        {
            printf("Array data is:%s\r\n",mpudata);
        }else delay_ms(10);
		i++;
		if((i%50)==0) LED0_Toggle;
	}   
}

