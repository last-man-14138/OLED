
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

#ifndef __GUI_H__
#define __GUI_H__
#include "stm32f4xx_hal.h"

void OLED_draw_point(uint8_t x,uint8_t y,uint8_t d);
void OLED_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void OLED_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void OLED_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);
void OLED_gui_circle(int xc, int yc,uint16_t c,int r, int fill);
void OLED_display_string_5x8(unsigned char column,unsigned char row,unsigned char reverse,unsigned char *text);
void OLED_display_string_8x16(uint8_t column,uint8_t row,uint8_t *text);
void OLED_display_string_12x24(uint8_t column,uint8_t row,uint8_t *text);
void OLED_display_string_16x32(uint8_t column,uint8_t row,uint8_t *text);
void OLED_display_string_16x16(uint8_t column,uint8_t row,uint8_t *text);
void OLED_disp_string_8x16_16x16(uint8_t column,uint8_t row,uint8_t *text);
void OLED_put_Char(unsigned char C);
void OLED_put_String(const char *String);	
void OLED_disp_pic_BMP(uint8_t x, uint8_t y,const unsigned char *pic,char value,uint32_t len);
void OLED_show_run_page(void);
void OLED_modify_num(uint8_t x, uint8_t y,uint32_t num,uint8_t type);
#endif
