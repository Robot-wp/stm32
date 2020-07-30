#include "ADC.h"

uint16_t  ADCBuf[9] = {0x00};					// ADC数据缓存

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
*  
*       ADC通道               对应端口                采集数据信息
*        ADC14                  PC4                   温度ADC采集
*        ADC15                  PC5                   湿度ADC采集
************************************************************************************************************************
*/
void ADC_Init_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
        
  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);				// 使能DMA时钟
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);			// 使能ADC1时钟
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;	  
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//  	GPIO_Init(GPIOA, &GPIO_InitStructure);

//  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			     
//  	GPIO_Init(GPIOB, &GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;	 
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//DMA1通道1配置
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;					// DMA通道外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCBuf[0];				// DMA通道存储器地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;							// 外设为源地址
	DMA_InitStructure.DMA_BufferSize = 2;										// 缓存大小为8
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			// 外设寄存器地址不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						// 存储器地址不变
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 数据宽度16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			// 存储器数据宽度16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;								// 环形缓冲模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;							// 优先级设置高
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;								// 禁止DMA通道存储器到存储器传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);								// 初始化DMA1通道1
	  
	DMA_Cmd(DMA1_Channel1, ENABLE);												//使能DMA1的通道1
	     
	// ADC1 配置
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;							// 独立模式  CR1
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;								// 扫描模式使能
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;							// 连续转换模式使能
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;			// 启动转换的外部事件--无  CR2
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;						// 转换后的数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 2;										// 转换的通道数为8
	ADC_Init(ADC1, &ADC_InitStructure);
	
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);	    //通道AIN1采样时间及转换顺序
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_55Cycles5);	    //通道AIN4采样时间及转换顺序
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 3, ADC_SampleTime_55Cycles5);	    //通道AIN5采样时间及转换顺序
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 4, ADC_SampleTime_55Cycles5);	    //通道AIN8采样时间及转换顺序
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 5, ADC_SampleTime_55Cycles5);	//通道AIN11采样时间及转换顺序
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 6, ADC_SampleTime_55Cycles5);	//通道AIN12采样时间及转换顺序
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 7, ADC_SampleTime_55Cycles5);	//通道AIN13采样时间及转换顺序
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_55Cycles5);	//通道AIN14采样时间及转换顺序	
    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 2, ADC_SampleTime_55Cycles5);    //通道AIN15采样时间及转换顺序	
													  
	ADC_DMACmd(ADC1, ENABLE);		                          					//允许ADC1进行DMA传送
	ADC_Cmd(ADC1, ENABLE);														//使能ADC1
	
	ADC_ResetCalibration(ADC1);													//允许ADC1复位校准寄存器 
	while(ADC_GetResetCalibrationStatus(ADC1));									//检测校准寄存器是否复位完成 
	
	ADC_StartCalibration(ADC1);													//启动ADC1 校准

	while(ADC_GetCalibrationStatus(ADC1));									    //检测校准是否完成 
	     
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);										// 开始转换    
    
}


































