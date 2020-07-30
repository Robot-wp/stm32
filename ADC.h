#ifndef __ADC_H__
#define __ADC_H__


#include "includes.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"


// ADC���ݼĴ�������ַ
#define ADC1_DR_Address    ((uint32_t)0x4001244C)


// ADCͨ������
#define  AIN1_CH	    0 						 // �ⲿ����ͨ��1
#define  AIN2_CH	    3 						 // �ⲿ����ͨ��2
#define  AIN3_CH	    6 						 // �ⲿ����ͨ��3
#define  AIN4_CH	    8 						 // �ⲿ����ͨ��4
#define  AIN5_CH	    9 						 // �ⲿ����ͨ��5
#define  AIN6_CH	    10						 // �ⲿ����ͨ��6
#define  AIN7_CH	    12 						 // �ⲿ����ͨ��7
#define  AIN8_CH	    13 						 // �ⲿ����ͨ��8



// ADC���ջ��涨��
extern uint16_t  ADCBuf[9];


/*
************************************************************************************************************************
*                                            ADC_Init_Config
*
* ����: ��ʼ��ADC
*
* ����: none
*
* ���أ�none
*
* ��ע: none
************************************************************************************************************************
*/
void ADC_Init_Config(void);

































#endif
