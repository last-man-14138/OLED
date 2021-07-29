
//********************************************************************************
//=========================================��Դ����================================================//
//    OLEDģ��             ��Ƭ��
//      5V        ��    DC5V��3.3V��Դ
//      GND       ��        GND                        
//======================================OLED�������߽���==========================================//
//��ģ��������������ΪIIC
//    OLEDģ��             ��Ƭ��
//      SCL       ��        PB13     // IICʱ���ź�
//      SDA       ��        PB14     // IIC�����ź�
//======================================OLED�������߽���==========================================//
//��ģ��������������ΪIIC������Ҫ�ӿ����ź���    
//=========================================����������=========================================//
//��ģ�鱾��������������Ҫ�Ӵ�������
//============================================================================================//
#ifndef __OLED_H
#define __OLED_H			  	 
#include "stm32f4xx_hal.h"
#include "stdlib.h"	
#include "i2c.h"
#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		128
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	128	    						  
		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

//OLED�����ú���
void OLED_WR_Byte(unsigned dat,unsigned cmd);     							   		    
void OLED_Init(void);
void OLED_Clear(uint8_t dat); 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd);
void OLED_transfer_col_data(unsigned char data1,unsigned char data2);
void OLED_transfer_col_data2(unsigned char data1,unsigned char data2,unsigned char gray_value);
void display_full_gray(uint8_t data1); 
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void LCD_SetContrast(uint16_t arr);
#endif
