/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-09-06
 * @brief       ����ͷ ʵ��
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ������ H743������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/SDRAM/sdram.h"
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/MPU/mpu.h"
#include "../User/glue.h"
#include "./BSP/LCD/ltdc.h"
#include "./BSP/DCMI/dcmi.h"
#include "./BSP/TIMER/btim.h"
#include "./BSP/OV5640/sccb.h"
#include "./BSP/USART2/usart2.h"
#include "./BSP/OV5640/ov5640.h"
#include "./BSP/PCF8574/pcf8574.h"


uint8_t g_ov_mode = 0;                                      /* bit0: 0, RGB565ģʽ;  1, JPEGģʽ */
uint16_t g_curline = 0;                                     /* ����ͷ�������,��ǰ�б�� */
uint16_t g_yoffset = 0;                                     /* y�����ƫ���� */

#define jpeg_buf_size       1 * 1024 * 1024                 /* ����JPEG���ݻ���jpeg_buf�Ĵ�С(*4�ֽ�) */
#define jpeg_line_size      4 * 1024                        /* ����DMA��������ʱ,һ�����ݵ����ֵ */

uint32_t g_dcmi_line_buf[2][jpeg_line_size] ;               /* RGB��ʱ,����ͷ����һ��һ�ж�ȡ,�����л��� */

#if !(__ARMCC_VERSION >= 6010050)                           /* ����AC6����������ʹ��AC5������ʱ */

uint32_t g_jpeg_data_buf[jpeg_buf_size]  __attribute__((at(0XC0000000 + 1280 * 800 * 2)));     /* JPEG���ݻ���buf,������LCD֡����֮�� */

#else   /* ʹ��AC6������ʱ */

uint32_t g_jpeg_data_buf[jpeg_buf_size]  __attribute__((section(".bss.ARM.__at_0XC01F4000"))); /* JPEG���ݻ���buf,������LCD֡����֮�� */


#endif


volatile uint32_t g_jpeg_data_len = 0;                      /* buf�е�JPEG��Ч���ݳ��� */

/**
 * 0,����û�вɼ���;
 * 1,���ݲɼ�����,���ǻ�û����;
 * 2,�����Ѿ����������,���Կ�ʼ��һ֡����
 */
volatile uint8_t g_jpeg_data_ok = 0;                        /* JPEG���ݲɼ���ɱ�־ */

/* JPEG�ߴ�֧���б� */
const uint16_t jpeg_img_size_tbl[][2] =
{
    160, 120,       /* QQVGA */
    320, 240,       /* QVGA */
    640, 480,       /* VGA */
    800, 600,       /* SVGA */
    1024, 768,      /* XGA */
    1280, 800,      /* WXGA */
    1440, 900,      /* WXGA+ */
    1280, 1024,     /* SXGA */
    1600, 1200,     /* UXGA */
    1920, 1080,     /* 1080P */
    2048, 1536,     /* QXGA */
    2592, 1944,     /* 500W */
};

const char *EFFECTS_TBL[7] = {"Normal", "Cool", "Warm", "B&W", "Yellowish ", "Inverse", "Greenish"};                    /* 7����Ч */
const char *JPEG_SIZE_TBL[12] = {"QQVGA","QVGA","VGA","SVGA","XGA","WXGA","WXGA+","SXGA","UXGA","1080P","QXGA","500W"}; /* JPEGͼƬ 12�ֳߴ� */

/**
 * @brief       ����JPEG����
 * @ntoe        ��DCMI_IRQHandler�жϷ��������汻����
 *              ���ɼ���һ֡JPEG���ݺ�,���ô˺���,�л�JPEG BUF.��ʼ��һ֡�ɼ�.
 *
 * @param       ��
 * @retval      ��
 */
void jpeg_data_process(void)
{
    uint16_t i;
    uint16_t rlen;                                                                /* ʣ�����ݳ��� */
    uint32_t *pbuf;
    g_curline = g_yoffset;

    if (g_ov_mode & 0X01)                                                         /* ֻ����JPEG��ʽ��,����Ҫ������. */
    {
        if (g_jpeg_data_ok == 0)                                                  /* jpeg���ݻ�δ�ɼ���? */
        {
            __HAL_DMA_DISABLE(&g_dma_dcmi_handle);                                /* �ر�DMA */

            rlen = jpeg_line_size - __HAL_DMA_GET_COUNTER(&g_dma_dcmi_handle);    /* �õ�ʣ�೤�� */
            pbuf = g_jpeg_data_buf + g_jpeg_data_len;                             /* ƫ�Ƶ���Ч����ĩβ,�������� */

            if (DMA1_Stream1->CR & (1 << 19))
            {
                for (i = 0; i < rlen; i++)
                {
                    pbuf[i] = g_dcmi_line_buf[1][i];                              /* ��ȡbuf1�����ʣ������ */
                }
            }
            else
            {
                for (i = 0; i < rlen; i++)
                {
                    pbuf[i] = g_dcmi_line_buf[0][i];                              /* ��ȡbuf0�����ʣ������ */
                }
            }
            g_jpeg_data_len += rlen;                                              /* ����ʣ�೤�� */
            g_jpeg_data_ok = 1;                                                   /* ���JPEG���ݲɼ����,�ȴ������������� */
        }
        if (g_jpeg_data_ok == 2)                                                  /* ��һ�ε�jpeg�����Ѿ��������� */
        {
            __HAL_DMA_SET_COUNTER(&g_dma_dcmi_handle, jpeg_line_size);            /* ���䳤��Ϊjpeg_buf_size*4�ֽ� */
            __HAL_DMA_ENABLE(&g_dma_dcmi_handle);                                 /* ���´��� */
            g_jpeg_data_ok = 0;                                                   /* �������δ�ɼ� */
            g_jpeg_data_len = 0;                                                  /* �������¿�ʼ */
        }
    }
    else
    {
        if (lcdltdc.pwidth == 0)
        {
            lcd_set_cursor(0, 0);
            lcd_write_ram_prepare();                                              /* ��ʼд��GRAM */
        }
    }
}

/**
 * @brief       JPEG���ݽ��ջص�����
 * @ntoe        ��DMA1_Stream1_IRQHandler�жϷ��������汻����
 *
 * @param       ��
 * @retval      ��
 */
void jpeg_dcmi_rx_callback(void)
{
    uint16_t i;
    uint32_t *pbuf;
    pbuf = g_jpeg_data_buf + g_jpeg_data_len;               /* ƫ�Ƶ���Ч����ĩβ */

    if (DMA1_Stream1->CR & (1 << 19))                       /* buf0����,��������buf1 */
    {
        for (i = 0; i < jpeg_line_size; i++)
        {
            pbuf[i] = g_dcmi_line_buf[0][i];                /* ��ȡbuf0��������� */
        }
        
        g_jpeg_data_len += jpeg_line_size;                  /* ƫ�� */
    }
    else                                                    /* buf1����,��������buf0 */
    {
        for (i = 0; i < jpeg_line_size; i++)
        {
            pbuf[i] = g_dcmi_line_buf[1][i];                /* ��ȡbuf1��������� */
        }
        
        g_jpeg_data_len += jpeg_line_size;                  /* ƫ�� */
    }
    SCB_CleanInvalidateDCache();                            /* �����Ч��DCache */
}

/**
 * @brief       RGB�����ݽ��ջص�����
 * @param       ��
 * @retval      ��
 */
void rgblcd_dcmi_rx_callback(void)
{  
    uint16_t *pbuf;

    if (DMA1_Stream1 -> CR & (1 << 19))                              /* DMAʹ��buf1,��ȡbuf0 */
    { 
        pbuf = (uint16_t *)g_dcmi_line_buf[0]; 
    }
    else                                                             /* DMAʹ��buf0,��ȡbuf1 */
    {
        pbuf = (uint16_t *)g_dcmi_line_buf[1]; 
    }
    ltdc_color_fill(0, g_curline,lcddev.width - 1, g_curline, pbuf); /* DM2D��� */ 

    if (g_curline < lcddev.height)
    {
        g_curline++;
    }
}

/**
 * @brief       JPEG����
 * @ntoe        JPEG����,ͨ������2���͸�����.
 * @param       ��
 * @retval      ��
 */
void jpeg_test(void)
{
    uint8_t key;
    uint8_t *p, headok;
    uint32_t i, jpgstart, jpglen;
    uint8_t effect = 0, contrast = 2;
    uint8_t msgbuf[15];              /* ��Ϣ������ */
    uint8_t size = 2;                /* Ĭ����QVGA 320*240�ߴ� */
    
    lcd_clear(WHITE);
    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "OV5640 JPEG Mode", RED);
    lcd_show_string(30, 100, 200, 16, 16, "KEY0:Contrast", RED);        /* �Աȶ� */
    lcd_show_string(30, 120, 200, 16, 16, "KEY1:AUTO Focus", RED);      /* �Զ��Խ� */
    lcd_show_string(30, 140, 200, 16, 16, "KEY2:Effect", RED);          /* ��Ч */
    lcd_show_string(30, 160, 200, 16, 16, "KEY_UP:Size", RED);          /* �ֱ������� */
    sprintf((char *)msgbuf, "JPEG Size:%s", JPEG_SIZE_TBL[size]);
    lcd_show_string(30, 180, 200, 16, 16, (char *)msgbuf, RED);         /* ��ʾ��ǰJPEG�ֱ��� */
    
    ov5640_rgb565_mode();                        /* RGB565ģʽ */
    ov5640_focus_init();

    ov5640_jpeg_mode();                          /* JPEGģʽ */
    ov5640_light_mode(0);                        /* �Զ�ģʽ */
    ov5640_color_saturation(3);                  /* ɫ�ʱ��Ͷ�0 */
    ov5640_brightness(4);                        /* ����0 */
    ov5640_contrast(3);                          /* �Աȶ�0 */
    ov5640_sharpness(33);                        /* �Զ���� */
    ov5640_focus_constant();                     /* ���������Խ� */
    dcmi_init();                                 /* DCMI���� */
    dcmi_rx_callback = jpeg_dcmi_rx_callback;    /* JPEG�������ݻص����� */
    dcmi_dma_init((uint32_t)&g_dcmi_line_buf[0], (uint32_t)&g_dcmi_line_buf[1], jpeg_line_size, DMA_MDATAALIGN_WORD, DMA_MINC_ENABLE); /* DCMI DMA���� */

    ov5640_outsize_set(4, 0, jpeg_img_size_tbl[size][0], jpeg_img_size_tbl[size][1]);   /* ��������ߴ� */
    dcmi_start();                                                                       /* �������� */

    while (1)
    { 
        if (g_jpeg_data_ok == 1)                                                        /* �Ѿ��ɼ���һ֡ͼ���� */
        {  
            p = (uint8_t *)g_jpeg_data_buf;
            lcd_show_string(30, 210, 210, 16, 16, "Sending JPEG data...", RED);         /* ��ʾ���ڴ������� */

            jpglen = 0;                                                                 /* ����jpg�ļ���СΪ0 */
            headok = 0;                                                                 /* ���jpgͷ��� */
            for (i = 0; i < g_jpeg_data_len * 4; i++)                                   /* ����0XFF,0XD8��0XFF,0XD9,��ȡjpg�ļ���С */
            {
                if ((p[i] == 0XFF) && (p[i + 1] == 0XD8))                               /* �ҵ�FF D8  */
                {
                    jpgstart = i;
                    headok = 1;                                                         /* ����ҵ�jpgͷ(FF D8) */
                }
                if ((p[i] == 0XFF) && (p[i + 1] == 0XD9) && headok)                     /* �ҵ�ͷ�Ժ�,����FF D9 */
                {
                    jpglen = i - jpgstart + 2;
                    break;
                }
            }
            if (jpglen)                                                                  /* ������jpeg���� */
            {
                                printf("JPEG:%u bytes\r\n", jpglen);
                p += jpgstart;                                                           /* ƫ�Ƶ�0XFF,0XD8�� */
                if (p[2] == 0xFF && p[3] == 0xA0) { p[3] = 0xE0; SCB_CleanDCache(); } /* FF A0->FF E0 */
                for (i = 0; i < jpglen; i++)                                             /* ��������jpg�ļ� */
                {
                    USART2->TDR = p[i];  
                    while ((USART2->ISR & 0X40) == 0);                                   /* ѭ������,ֱ��������� */ 
                    
                    key = key_scan(0); 
                    if (key)break;
                }  
            }
            if (key)                                                                     /* �а�������,��Ҫ���� */
            {  
                lcd_show_string(30, 210, 210, 16, 16, "Quit Sending data   ", RED);      /* ��ʾ�˳����ݴ��� */
                switch (key)
                {
                    case KEY0_PRES:                                                      /* �Աȶ����� */
                        contrast++;
                        if (contrast > 6)contrast = 0;
                        ov5640_contrast(contrast);
                        sprintf((char *)msgbuf, "Contrast:%d", (signed char)contrast - 3);
                        break;
                    
                    case KEY1_PRES:                                                      /* ִ��һ���Զ��Խ� */
                        ov5640_focus_single();
                        break;
                    
                    case KEY2_PRES:                                                      /* ��Ч���� */ 
                        effect++;
                        if (effect > 6)effect = 0;
                        ov5640_special_effects(effect);                                  /* ������Ч */
                        sprintf((char *)msgbuf, "%s", EFFECTS_TBL[effect]);
                        break;
                    
                    case WKUP_PRES:                                                      /* JPEG����ߴ����� */
                        size++;  
                        if (size > 11)size = 0;   
                        ov5640_outsize_set(16, 4, jpeg_img_size_tbl[size][0], jpeg_img_size_tbl[size][1]); /* ��������ߴ� */
                        sprintf((char *)msgbuf, "JPEG Size:%s", JPEG_SIZE_TBL[size]);
                        break;
                }

                key = 0;                                                                 /* �����ظ����� */
                lcd_fill(30, 180, 239, 190 + 16, WHITE);
                lcd_show_string(30, 180, 210, 16, 16, (char *)msgbuf, RED);              /* ��ʾ��ʾ���� */
                delay_ms(800);
            }
            else 
            {
                lcd_show_string(30, 210, 210, 16, 16, "Send data complete!!", RED);      /* ��ʾ����������� */
            }

            g_jpeg_data_ok = 2;     /* ���jpeg���ݴ�������,������DMAȥ�ɼ���һ֡��. */
        }
    }
}

/**
 * @brief       RGB565����
 * @ntoe        RGB����ֱ����ʾ��LCD����
 * @param       ��
 * @retval      ��
 */
void rgb565_test(void)
{
    uint8_t key;
    float fac = 0;
    uint8_t effect = 0, contrast = 2;
    uint8_t scale = 1;                                                      /* Ĭ����ȫ�ߴ����� */
    uint8_t msgbuf[15];                                                     /* ��Ϣ������ */
    uint16_t outputheight = 0;

    lcd_clear(WHITE);
    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "OV5640 RGB565 Mode", RED);
    lcd_show_string(30, 100, 200, 16, 16, "KEY0:Contrast", RED);            /* �Աȶ� */
    lcd_show_string(30, 120, 200, 16, 16, "KEY1:AUTO Focus", RED);          /* ִ���Զ��Խ� */
    lcd_show_string(30, 140, 200, 16, 16, "KEY2:Effects", RED);             /* ��Ч */
    lcd_show_string(30, 160, 200, 16, 16, "KEY_UP:FullSize/Scale", RED);    /* 1:1�ߴ�(��ʾ��ʵ�ߴ�)/ȫ�ߴ����� */

    /* �Զ��Խ���ʼ�� */
    ov5640_rgb565_mode();          /* RGB565ģʽ */ 
    ov5640_focus_init();

    ov5640_light_mode(0);          /* �Զ�ģʽ */
    ov5640_color_saturation(3);    /* ɫ�ʱ��Ͷ�0  */
    ov5640_brightness(4);          /* ����0 */
    ov5640_contrast(3);            /* �Աȶ�0 */
    ov5640_sharpness(33);          /* �Զ���� */
    ov5640_focus_constant();       /* ���������Խ� */
    dcmi_init();                   /* DCMI���� */

    if (lcdltdc.pwidth != 0)       /* RGB�� */
    {
        dcmi_rx_callback = rgblcd_dcmi_rx_callback;                         /* RGB���������ݻص����� */
        dcmi_dma_init((uint32_t)g_dcmi_line_buf[0], (uint32_t)g_dcmi_line_buf[1], lcddev.width / 2, DMA_MDATAALIGN_HALFWORD, DMA_MINC_ENABLE);
        BTIM_TIMX_INT->CR1&=~(0x01);  /* �رն�ʱ��,�ر�֡��ͳ�ƣ��򿪵Ļ���RGB�����ڴ��ڴ�ӡ��ʱ�򣬻ᶶ */
    }
    else                                                                    /* MCU �� */
    {
        dcmi_dma_init((uint32_t)&LCD->LCD_RAM, 0, 1, DMA_MDATAALIGN_HALFWORD, DMA_MINC_DISABLE);
    }

    if (lcddev.height == 1024)
    {
        g_yoffset = (lcddev.height - 800) / 2;
        outputheight = 800;
        ov5640_write_reg(0x3035, 0X51);                                     /* �������֡�ʣ�������ܶ��� */
    }
    else if (lcddev.height == 1280)
    {
        g_yoffset = (lcddev.height - 600) / 2;
        outputheight = 600;
        ov5640_write_reg(0x3035, 0X51);                                     /* �������֡�ʣ�������ܶ��� */
    }
    else 
    {
        g_yoffset = 0;
        outputheight = lcddev.height;
    }

    g_curline = g_yoffset;                                                  /* ������λ */
    ov5640_outsize_set(4, 0, lcddev.width, outputheight);                   /* ����������ʾ */
    dcmi_start();                                                           /* �������� */
    lcd_clear(0xFFFF);
    
    while (1)
    { 
        key = key_scan(0); 

        if (key)
        { 
            if (key != KEY1_PRES)dcmi_stop();                               /* ��KEY1����,ֹͣ��ʾ */
            switch (key)
            {
                case KEY0_PRES:                                             /* �Աȶ����� */
                    contrast++;
                    if (contrast > 6)
                    {
                        contrast = 0;
                    }
                    ov5640_contrast(contrast);
                    sprintf((char *)msgbuf, "Contrast:%d", (signed char)contrast - 3);
                    break;

                case KEY1_PRES:                                             /* ִ��һ���Զ��Խ� */
                    ov5640_focus_single();
                    break;

                case KEY2_PRES:                                             /* ��Ч���� */
                    effect++;
                    if (effect > 6)
                    {
                        effect = 0;
                    }
                    ov5640_special_effects(effect);                         /* ������Ч */
                    sprintf((char *)msgbuf, "%s", EFFECTS_TBL[effect]);
                    break;

                case WKUP_PRES:                                             /* 1:1�ߴ�(��ʾ��ʵ�ߴ�)/���� */   
                    scale =! scale;
                    if (scale == 0)
                    {
                        fac = (float)800 / outputheight;                    /* �õ��������� */
                        ov5640_outsize_set((1280 - fac * lcddev.width) / 2, (800 - fac * outputheight) / 2, lcddev.width, outputheight);      
                        sprintf((char *)msgbuf, "Full Size 1:1");
                    }
                    else 
                    {
                        ov5640_outsize_set(4, 0, lcddev.width, outputheight);
                        sprintf((char *)msgbuf, "Scale");
                    }
                    break;
            }
            if (key != KEY1_PRES)                                           /* ��KEY1���� */
            {
                lcd_show_string(30, 50, 210, 16, 16, (char *)msgbuf, RED);  /* ��ʾ��ʾ����  */
                delay_ms(800); 
                dcmi_start();                                               /* ���¿�ʼ���� */
            }
        } 
        delay_ms(10);
    }
} 

int main(void)
{
    uint8_t key = 0;
    uint16_t t = 0;

    sys_cache_enable();                          /* ��L1-Cache */
    HAL_Init();                                  /* ��ʼ��HAL�� */
    sys_stm32_clock_init(160, 5, 2, 4);          /* ����ʱ��, 400Mhz */
    delay_init(400);                             /* ��ʱ��ʼ�� */
    usart_init(115200);                          /* ���ڳ�ʼ�� */
    usart2_init(115200);                         /* ��ʼ������2������Ϊ921600 */
    usmart_init(200);                            /* ��ʼ��USMART */
    mpu_memory_protection();                     /* ������ش洢���� */
    led_init();                                  /* ��ʼ��LED */
    key_init();                                  /* ��ʼ��KEY */
    sdram_init();                                /* ��ʼ��SDRAM */
    lcd_init();                                  /* ��ʼ��LCD */
    btim_timx_int_init(10000 - 1, 20000 - 1);    /* 10KHz����Ƶ�ʣ�1���ж�һ�� */

    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "OV5640 TEST", RED);
    lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);
                   
    while (ov5640_init())                        /* ��ʼ��OV5640 */
    {
        lcd_show_string(30, 130, 240, 16, 16, "OV5640 ERROR", RED);
        printf("OV5640 ERROR, retrying...\r\n");
        delay_ms(200);
        lcd_fill(30, 130, 239, 170, WHITE);
        delay_ms(200);
        LED0_TOGGLE();
    }

    lcd_show_string(30, 130, 200, 16, 16, "OV5640 OK", RED);
    printf("OV5640 OK, entering JPEG mode\r\n");
    glue_run();
    g_ov_mode = 1;

if (g_ov_mode == 1)
    {
        jpeg_test();
    }
    else
    {
        rgb565_test();
    }
}


