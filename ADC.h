#ifndef __ADC_H__
#define __ADC_H__


#include "includes.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"


// ADC数据寄存器基地址
#define ADC1_DR_Address    ((uint32_t)0x4001244C)


// ADC通道定义
#define  AIN1_CH	    0 						 // 外部输入通道1
#define  AIN2_CH	    3 						 // 外部输入通道2
#define  AIN3_CH	    6 						 // 外部输入通道3
#define  AIN4_CH	    8 						 // 外部输入通道4
#define  AIN5_CH	    9 						 // 外部输入通道5
#define  AIN6_CH	    10						 // 外部输入通道6
#define  AIN7_CH	    12 						 // 外部输入通道7
#define  AIN8_CH	    13 						 // 外部输入通道8



// ADC接收缓存定义
extern uint16_t  ADCBuf[9];


/*
************************************************************************************************************************
*                                            ADC_Init_Config
*
* 描述: 初始化ADC
*
* 参数: none
*
* 返回：none
*
* 备注: none
************************************************************************************************************************
*/
void ADC_Init_Config(void);

































#endif
