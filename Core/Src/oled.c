
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


#include "oled.h"
#include "i2c.h"
#include "stdlib.h"	 
//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 	
		   
//******************************************************************
//��������  OLED_WR_Byte
    
    
//���ܣ�    ͨ��IIC��������д��һ���ֽ�����
//���������dat����д�������
//          cmd��0-���1-����
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
		Write_IIC_Data(dat);
  }
	else 
	{
		Write_IIC_Command(dat);		
	}
}



//******************************************************************
//��������  OLED_Set_Pos
//���ܣ�    ���õ�����
//���������x,y������ֵ��һ��x��ʾ2��
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0x75,OLED_CMD);
	OLED_WR_Byte(x,OLED_CMD);
	OLED_WR_Byte(x+7,OLED_CMD);

	OLED_WR_Byte(0x15,OLED_CMD);
	OLED_WR_Byte(y,OLED_CMD);
	OLED_WR_Byte(y,OLED_CMD);
}   	  
	   			 
//******************************************************************
//��������  OLED_Clear
//���ܣ�    ��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
//���������dat��0-��ɫ��0xFF-��ɫ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************	  
void OLED_Clear(uint8_t dat)  
{  
	unsigned int i,j;
  OLED_WR_Byte(0x15,OLED_CMD);
  OLED_WR_Byte(0x00,OLED_CMD);
  OLED_WR_Byte(0x3f,OLED_CMD);

  OLED_WR_Byte(0x75,OLED_CMD);
  OLED_WR_Byte(0x00,OLED_CMD);
  OLED_WR_Byte(0x7f,OLED_CMD);

	for(i=0;i<128;i++) 
  {
    for(j=0;j<64;j++)
     {
      OLED_WR_Byte(dat,OLED_DATA);//RAM data write
     }
  }
}

//******************************************************************
//��������  OLED_SetWindows
//���ܣ�    ������ʾ����  
//���������xStart��yStart�������������
//          xEnd��yEnd�������յ�����
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void OLED_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd)
{
	OLED_WR_Byte(0x15,OLED_CMD);
	OLED_WR_Byte(xStar,OLED_CMD);
	OLED_WR_Byte(xEnd,OLED_CMD);

	OLED_WR_Byte(0x75,OLED_CMD);
	OLED_WR_Byte(yStar,OLED_CMD);
	OLED_WR_Byte(yEnd,OLED_CMD);
}

//******************************************************************
//��������  LCD_SetContrast
//���ܣ�    ��������Ҷ�ֵ  
//���������arr���Ҷ�ֵ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_SetContrast(uint16_t arr)
{
	 OLED_WR_Byte(0x81,OLED_CMD);  // set contrast control
   OLED_WR_Byte(arr,OLED_CMD);
}

//******************************************************************
//��������  OLED_transfer_col_data
//���ܣ�    ���õ�������ɫֵ	  
//���������data1����һ������ɫ����
//          data2���ڶ�������ɫ����
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void OLED_transfer_col_data(unsigned char data1,unsigned char data2)
{
  unsigned char i; 
	 	for(i=0;i<8;i++)
	{
          if ((data1& 0x01)&&(data2& 0x01))	
		    { 	
		  			OLED_WR_Byte(0xFF,OLED_DATA);              //4BIT��ʾ���ȣ���������0~F��16���Ҷ�
							//LCD_WR_DATA(0xF8);              //4BIT��ʾ���ȣ���������0~F��16���Ҷ�
			  }
        else  if  ((data1& 0x01)==1&&(data2& 0x01)==0)				
		    {
			       
              OLED_WR_Byte(0xF0,OLED_DATA);   
        }
        else  if  ((data1& 0x01)==0&&(data2& 0x01)==1)				
		    {
			       
              OLED_WR_Byte(0x0F,OLED_DATA);  
        }
        else  if  ((data1& 0x01)==0&&(data2& 0x01)==0)				
		    {
			       
              OLED_WR_Byte(0x00,OLED_DATA);  
        }
 
        data1>>= 1;
        data2>>= 1;
    }
  
}

//******************************************************************
//��������  OLED_transfer_col_data2
//���ܣ�    ���õ�������ɫֵ	  
//���������data1����һ������ɫ����
//          data2���ڶ�������ɫ����
//					gray_value���Ҷ�ֵ
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void OLED_transfer_col_data2(unsigned char data1,unsigned char data2,unsigned char gray_value)
{
  unsigned char i; 
	 	for(i=0;i<8;i++)
	{
          if ((data1& 0x01)&&(data2& 0x01))	
		    { 	
						OLED_WR_Byte((gray_value<<4)|gray_value,OLED_DATA);//4BIT��ʾ���ȣ���������0~F��16���Ҷ�		  			            
			  }
        else  if  ((data1& 0x01)==1&&(data2& 0x01)==0)				
		    {
			       OLED_WR_Byte((gray_value<<4)&0xF0,OLED_DATA); 
        }
        else  if  ((data1& 0x01)==0&&(data2& 0x01)==1)				
		    {
			       OLED_WR_Byte((gray_value)&0x0F,OLED_DATA);   
        }
        else  if  ((data1& 0x01)==0&&(data2& 0x01)==0)				
		    {
			       
              OLED_WR_Byte(0x00,OLED_DATA);  
        }
        data1>>= 1;
        data2>>= 1;
    } 
}

//******************************************************************
//��������  display_full_gray
//���ܣ�    ��ʾȫ���Ҷ�ֵ  
//���������data1���Ҷ�ֵ
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void display_full_gray(uint8_t data1)
{
  int i,j;
  OLED_WR_Byte(0x15,OLED_CMD);
  OLED_WR_Byte(0x00,OLED_CMD);
  OLED_WR_Byte(0x3f,OLED_CMD);

  OLED_WR_Byte(0x75,OLED_CMD);
  OLED_WR_Byte(0x00,OLED_CMD);
  OLED_WR_Byte(0x7f,OLED_CMD);
  for(i=0;i<128;i++) 
  {
    for(j=0;j<64;j++)
     {
      OLED_WR_Byte(data1,OLED_DATA);
     }
  }

}

//******************************************************************
//��������  OLED_Init
//���ܣ�    ��ʼ��SSD1327	  
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 				    
void OLED_Init(void)
{ 		 
	MX_GPIO_Init();
	HAL_Delay(200);
	OLED_WR_Byte(0xae,OLED_CMD);     //display off

   OLED_WR_Byte(0x15,OLED_CMD);    //   set column address
   OLED_WR_Byte(0x00,OLED_CMD);    //  start column   0
   OLED_WR_Byte(0x7f,OLED_CMD);    //  end column   127

   OLED_WR_Byte(0x75,OLED_CMD);    //   set row address
   OLED_WR_Byte(0x00,OLED_CMD);    //  start row   0
   OLED_WR_Byte(0x7f,OLED_CMD);    //  end row   127
   OLED_WR_Byte(0x81,OLED_CMD);  // set contrast control
   OLED_WR_Byte(0x80,OLED_CMD);
   OLED_WR_Byte(0xa0,OLED_CMD);    // gment remap
   OLED_WR_Byte(0x51,OLED_CMD);   //
   OLED_WR_Byte(0xa1,OLED_CMD);  // start line
   OLED_WR_Byte(0x00,OLED_CMD);
   OLED_WR_Byte(0xa2,OLED_CMD);  // display offset
   OLED_WR_Byte(0x00,OLED_CMD);
   OLED_WR_Byte(0xa4,OLED_CMD);    // rmal display
   OLED_WR_Byte(0xa8,OLED_CMD);    // set multiplex ratio
   OLED_WR_Byte(0x7f,OLED_CMD); 
   OLED_WR_Byte(0xb1,OLED_CMD);  // set phase leghth
   OLED_WR_Byte(0xf1,OLED_CMD);
   OLED_WR_Byte(0xb3,OLED_CMD);  // set dclk
   OLED_WR_Byte(0x00,OLED_CMD);  //80Hz:0xc1 90Hz:0xe1   100Hz:0x00   110Hz:0x30 120Hz:0x50   130Hz:0x70     01
   OLED_WR_Byte(0xab,OLED_CMD);  // 
   OLED_WR_Byte(0x01,OLED_CMD);  //
   OLED_WR_Byte(0xb6,OLED_CMD);  // set phase leghth
   OLED_WR_Byte(0x0f,OLED_CMD);
   OLED_WR_Byte(0xbe,OLED_CMD);
   OLED_WR_Byte(0x0f,OLED_CMD);
   OLED_WR_Byte(0xbc,OLED_CMD);
   OLED_WR_Byte(0x08,OLED_CMD);
   OLED_WR_Byte(0xd5,OLED_CMD);
   OLED_WR_Byte(0x62,OLED_CMD);  
   OLED_WR_Byte(0xfd,OLED_CMD);
   OLED_WR_Byte(0x12,OLED_CMD);
   OLED_WR_Byte(0xaf,OLED_CMD); 
	 
}  





























