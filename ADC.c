#include "ADC.h"

uint16_t  ADCBuf[9] = {0x00};					// ADC���ݻ���

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
*  
*       ADCͨ��               ��Ӧ�˿�                �ɼ�������Ϣ
*        ADC14                  PC4                   �¶�ADC�ɼ�
*        ADC15                  PC5                   ʪ��ADC�ɼ�
************************************************************************************************************************
*/
void ADC_Init_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
        
  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);				// ʹ��DMAʱ��
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);			// ʹ��ADC1ʱ��
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;	  
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//  	GPIO_Init(GPIOA, &GPIO_InitStructure);

//  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			     
//  	GPIO_Init(GPIOB, &GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;	 
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//DMA1ͨ��1����
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;					// DMAͨ���������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCBuf[0];				// DMAͨ���洢����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;							// ����ΪԴ��ַ
	DMA_InitStructure.DMA_BufferSize = 2;										// �����СΪ8
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			// ����Ĵ�����ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						// �洢����ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // ���ݿ��16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			// �洢�����ݿ��16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;								// ���λ���ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;							// ���ȼ����ø�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;								// ��ֹDMAͨ���洢�����洢������
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);								// ��ʼ��DMA1ͨ��1
	  
	DMA_Cmd(DMA1_Channel1, ENABLE);												//ʹ��DMA1��ͨ��1
	     
	// ADC1 ����
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;							// ����ģʽ  CR1
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;								// ɨ��ģʽʹ��
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;							// ����ת��ģʽʹ��
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;			// ����ת�����ⲿ�¼�--��  CR2
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;						// ת����������Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 2;										// ת����ͨ����Ϊ8
	ADC_Init(ADC1, &ADC_InitStructure);
	
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);	    //ͨ��AIN1����ʱ�估ת��˳��
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_55Cycles5);	    //ͨ��AIN4����ʱ�估ת��˳��
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 3, ADC_SampleTime_55Cycles5);	    //ͨ��AIN5����ʱ�估ת��˳��
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 4, ADC_SampleTime_55Cycles5);	    //ͨ��AIN8����ʱ�估ת��˳��
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 5, ADC_SampleTime_55Cycles5);	//ͨ��AIN11����ʱ�估ת��˳��
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 6, ADC_SampleTime_55Cycles5);	//ͨ��AIN12����ʱ�估ת��˳��
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 7, ADC_SampleTime_55Cycles5);	//ͨ��AIN13����ʱ�估ת��˳��
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_55Cycles5);	//ͨ��AIN14����ʱ�估ת��˳��	
    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 2, ADC_SampleTime_55Cycles5);    //ͨ��AIN15����ʱ�估ת��˳��	
													  
	ADC_DMACmd(ADC1, ENABLE);		                          					//����ADC1����DMA����
	ADC_Cmd(ADC1, ENABLE);														//ʹ��ADC1
	
	ADC_ResetCalibration(ADC1);													//����ADC1��λУ׼�Ĵ��� 
	while(ADC_GetResetCalibrationStatus(ADC1));									//���У׼�Ĵ����Ƿ�λ��� 
	
	ADC_StartCalibration(ADC1);													//����ADC1 У׼

	while(ADC_GetCalibrationStatus(ADC1));									    //���У׼�Ƿ���� 
	     
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);										// ��ʼת��    
    
}


































