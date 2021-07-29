
//=========================================��Դ����================================================//
//    OLEDģ��             ��Ƭ��
//      5V        ��    DC5V��3.3V��Դ
//      GND       ��        GND                        
//======================================OLED�������߽���==========================================//
//��ģ��������������ΪIIC
//    OLEDģ��             ��Ƭ��
//      SCL       ��        PB13     // IICʱ���ź�
//      SDA       ��        PB14     // IIC�����ź�


#include "GUI.h"
#include "oled.h"
#include "oledfont.h" 
#include "stdio.h" 

const unsigned char  Chinese_text_16x16[] = 
{
	"ȫ�������ṩ���׽������Һ����ʾģ��ϵ�г�����ȫ�ӽǲ�Ʒ����������˫��ɫ�Է���͹��ĳ�����׼��������Ϊרע����רҵ����֧�ּ��Ҷ�"

};

//******************************************************************
//��������  OLED_draw_point
    
    
//���ܣ�    ����  
//���������x,y��������
//            d����ɫֵ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void OLED_draw_point(uint8_t x,uint8_t y,uint8_t d)
{
	OLED_Set_Pos(y, x);
	OLED_WR_Byte(d,OLED_DATA);
}

//******************************************************************
//��������  OLED_draw_line
    
    
//���ܣ�    ����
//���������x1,y1���������
//          x2,y2���յ�����
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void OLED_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
  uint8_t color;
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	
	for(t=0;t<=distance+1;t++ )//������� 
	{  
	xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) //����
		{ 
			xerr-=distance; 
			color=0xFF;
			OLED_draw_point(uRow,uCol,color);//���� 
			uRow+=incx; 
			
		} 
		if(yerr>distance) //����
		{ 
			yerr-=distance; 
			color=0xF0;
			OLED_draw_point(uRow,uCol,color);//���� 
			uCol+=incy; 
			/*
			color=0x00;
			GUI_Draw_2_pixel(uRow,uCol/2,color);//���� 
			uCol+=incy; */
			
		} 	
	}  
} 

//******************************************************************
//��������  OLED_draw_rectangle
    
    
//���ܣ�    ������
//���������x1,y1�������������
//          x2,y2�������յ�����
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void OLED_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	OLED_draw_line(x1,y1,x2,y1);
	OLED_draw_line(x1,y1+1,x1,y2);
	OLED_draw_line(x1,y2,x2,y2);
	OLED_draw_line(x2,y1,x2,y2);
} 

//******************************************************************
//��������  OLED_Fill
    
    
//���ܣ�    ������
//���������sx,sy�������������
//          ex,ey�������յ�����
//          color����ɫֵ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void OLED_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{  	

	uint16_t i,j;			
	uint16_t width=ex/2-sx/2+1; 		//�õ����Ŀ��
	uint16_t height=ey-sy+1;		//�߶�
	OLED_SetWindows(sx/2,sy,(ex-1)/2,ey-1);//������ʾ����
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		 OLED_WR_Byte(color,OLED_DATA);	//д������ 	 
	}

//	OLED_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ���������Ϊȫ��
}

void _draw_circle_8(int xc, int yc, int x, int y, uint16_t c)
{
	OLED_draw_point(xc + x, yc + y, c);

	OLED_draw_point(xc - x, yc + y, c);

	OLED_draw_point(xc + x, yc - y, c);

	OLED_draw_point(xc - x, yc - y, c);

	OLED_draw_point(xc + y, yc + x, c);

	OLED_draw_point(xc - y, yc + x, c);

	OLED_draw_point(xc + y, yc - x, c);

	OLED_draw_point(xc - y, yc - x, c);
}

//******************************************************************
//��������  gui_circle
    
    
//���ܣ�    ��ָ��λ�û�һ��ָ����С��Բ(���)
//���������(xc,yc) :Բ��������
//         	c:������ɫ
//		 	r:Բ�뾶
//		 	fill:����жϱ�־��1-��䣬0-�����
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************  
void OLED_gui_circle(int xc, int yc,uint16_t c,int r, int fill)
{
	int x = 0, y = r, yi, d;

	d = 3 - 2 * r;


	if (fill) 
	{
		// �����䣨��ʵ��Բ��
		while (x <= y) {
			for (yi = x; yi <= y; yi++)
				_draw_circle_8(xc, yc, x, yi, c);

			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	} else 
	{
		// �������䣨������Բ��
		while (x <= y) {
			_draw_circle_8(xc, yc, x, y, c);
			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
}

//******************************************************************
//��������  OLED_display_string_5x8
    
    
//���ܣ�    ��ʾ�ַ���Ϊ5����Ϊ8���ַ���  
//���������column������ʾ�ַ�����������
//          row������ʾ�ַ�����������
//          text������ʾ�ַ�����ָ��
//          reverse��0-������ʾ��1-��ɫ��ʾ
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void OLED_display_string_5x8(unsigned char column,unsigned char row,unsigned char reverse,unsigned char *text)
{
	unsigned int i=0,j,k,disp_data1,disp_data2;
	while(text[i]>0x00)
	{	
		if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			j=text[i]-0x20;

						for(k=0;k<2;k++)
						{
									if(reverse==1)
									{
										disp_data1=~ascii_table_5x8[j][2*k];
										disp_data2=~ascii_table_5x8[j][2*k+1];
									}
									else
									{
										 disp_data1=ascii_table_5x8[j][2*k];
										 disp_data2=ascii_table_5x8[j][2*k+1];
									}
									OLED_Set_Pos(row,column+k);
									OLED_transfer_col_data(disp_data1,disp_data2);
						}
						OLED_Set_Pos(row,column+2);

             if(reverse==1)
						{
									disp_data1=~ascii_table_5x8[j][4];
									disp_data2=0xff;
						}
						else
						{
							 disp_data1=ascii_table_5x8[j][4];
               disp_data2=0x00;                    //д��һ�пհ��У�ʹ��5x8���ַ����ַ�֮����һ�м����������
						}  
           OLED_transfer_col_data(disp_data1,disp_data2);
			i++;
			column+=3;
			if(column>63)
			{
				column=0;
	
			}
		}
		else
		i++;
	}
}

//******************************************************************
//��������  OLED_display_string_8x16
    
    
//���ܣ�    ��ʾ�ַ���Ϊ8����Ϊ16���ַ���  
//���������column������ʾ�ַ�����������
//          row������ʾ�ַ�����������
//          text������ʾ�ַ�����ָ��
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void OLED_display_string_8x16(uint8_t column,uint8_t row,uint8_t *text)
{
	uint16_t i=0,j,k,n;
	if(column>63)
	{
		column=0;

	}
	while(text[i]>0x00)
	{	
		if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			j=text[i]-0x20;
			for(n=0;n<2;n++)
			{			
				for(k=0;k<4;k++)   //����128�㣬ʵ��ֻ��64���У�ÿһ�п���2����
				{					
					OLED_Set_Pos(n*8+row,column+k);
				OLED_transfer_col_data(ascii_table_8x16[j][2*k+8*n],ascii_table_8x16[j][2*k+1+8*n]);	//д���ݵ�LCD  
				}
			}
			i++;
			column+=4;
		}
		else
		i++;
	}
}

//******************************************************************
//��������  OLED_display_string_12x24
    
    
//���ܣ�    ��ʾ�ַ���Ϊ12����Ϊ24���ַ���  
//���������column������ʾ�ַ�����������
//          row������ʾ�ַ�����������
//          text������ʾ�ַ�����ָ��
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void OLED_display_string_12x24(uint8_t column,uint8_t row,uint8_t *text)
{
	uint16_t i=0,j,k,n;
	if(column>63)
	{
		column=0;

	}
	while(text[i]>0x00)
	{	
		if((text[i]>=0x30)&&(text[i]<=0x39))
		{
			j=text[i]-0x30;
			for(n=0;n<3;n++)
			{			
				for(k=0;k<6;k++)   //����128�㣬ʵ��ֻ��64���У�ÿһ�п���2����
				{					
					OLED_Set_Pos(n*8+row,column+k);
				OLED_transfer_col_data(code_12x24[j][2*k+12*n],code_12x24[j][2*k+1+12*n]);	//д���ݵ�LCD  
				}
			}
			i++;
			column+=6;
		}
		else
		i++;
	}
}

//******************************************************************
//��������  OLED_display_string_16x32
    
    
//���ܣ�    ��ʾ�ַ���Ϊ16����Ϊ32���ַ���  
//���������column������ʾ�ַ�����������
//          row������ʾ�ַ�����������
//          text������ʾ�ַ�����ָ��
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void OLED_display_string_16x32(uint8_t column,uint8_t row,uint8_t *text)
{
	uint16_t i=0,j,k,n;
	if(column>63)
	{
		column=0;

	}
	while(text[i]>0x00)
	{	
		if((text[i]>=0x30)&&(text[i]<=0x39))
		{
			j=text[i]-0x30;
			for(n=0;n<4;n++)
			{			
				for(k=0;k<8;k++)   //����128�㣬ʵ��ֻ��64���У�ÿһ�п���2����
				{					
					OLED_Set_Pos(n*8+row,column+k);
				OLED_transfer_col_data(code_16x32[j][2*k+16*n],code_16x32[j][2*k+1+16*n]);	//д���ݵ�LCD  
				}
			}
			i++;
			column+=8;
		}
		else
		i++;
	}
}

//******************************************************************
//��������  OLED_display_string_16x16
    
    
//���ܣ�    ��ʾ�ַ���Ϊ16����Ϊ16���ַ���  
//���������column������ʾ�ַ�����������
//          row������ʾ�ַ�����������
//          text������ʾ�ַ�����ָ��
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void OLED_display_string_16x16(uint8_t column,uint8_t row,uint8_t *text)
{
    uint8_t i,j,k;
    uint32_t address; 
    
    j = 0;
    while(text[j] != '\0')
    {
        i = 0;
        address = 1;
        while(Chinese_text_16x16[i] > 0x7e)	  // >0x7f��˵������ASCII���ַ�
        {
            if(Chinese_text_16x16[i] == text[j])
            {
                if(Chinese_text_16x16[i + 1] == text[j + 1])
                {
                    address = i * 16;
                    break;
                }
            }
            i += 2;            
        }
        
        if(column >63)
        {
            column = 0;

        }
        
        if(address != 1)// ��ʾ����                   
        {
            
						for(k=0;k<2;k++)
						{
						
										for(i = 0; i < 8; i++)               
										{
									
                        OLED_Set_Pos(k*8+row,column+i);						       
                        OLED_transfer_col_data(Chinese_code_16x16[address],Chinese_code_16x16[address+1]);          								
											  address+=2;
											//delay_ms(10);
										}
										
						}
									j += 2;        
        }
        else              //û�����ֿ�ĺ��֣�����ʾ�հ��ַ�            
        {
						for(k=0;k<2;k++)
						{
						
										for(i = 0; i < 8; i++)      //8��col�൱��16����         
										{
											  OLED_Set_Pos(k*8+row,column+i);
									      OLED_transfer_col_data(0x00,0x00);   
										}
						}
									
									j++;
        }
        
        column+=7;
    }
}

//******************************************************************
//��������  OLED_disp_string_8x16_16x16
    
    
//���ܣ�    ��ʾ�ַ��ͺ��ֻ���ַ����������ַ����Ϊ8���߶�Ϊ16�����ֿ��Ϊ16���߶�Ϊ16 
//���������column������ʾ�ַ�������ʼ������
//          row������ʾ�ַ�������ʼ������
//          text������ʾ�ַ�����ָ��
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void OLED_disp_string_8x16_16x16(uint8_t column,uint8_t row,uint8_t *text)
{
    uint8_t temp[3];
    uint8_t i = 0;    
    
    while(text[i] != '\0')
    {
        if(text[i] > 0x7e)
        {
            temp[0] = text[i];
            temp[1] = text[i + 1];
            temp[2] = '\0';          //����Ϊ�����ֽ���
            OLED_display_string_16x16(column,row,temp);  //��ʾ����
            column += 8;
            i += 2;
        }
        else
        {
            temp[0] = text[i];    
            temp[1] = '\0';          //��ĸռһ���ֽ�
            OLED_display_string_8x16(column, row, temp);  //��ʾ��ĸ
            column += 4;             //4��8������
            i++;
        }
    }
}

uint8_t grayH= 0xF0;
uint8_t   grayL= 0x0F;
#define pgm_read_byte(STR) STR

//******************************************************************
//��������  OLED_put_Char
    
    
//���ܣ�    ��ʾһ���ַ�
//���������C������ʾ���ַ�
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void OLED_put_Char(unsigned char C)
{
	char c,bit1,bit2;
	char i,j;
    if(C < 32 || C > 127) //Ignore non-printable ASCII characters. This can be modified for multilingual font.
    {
        C=' '; //Space
    }   

    
    for(i=0;i<8;i=i+2)
    {
        for(j=0;j<8;j++)
        {
            // Character is constructed two pixel at a time using vertical mode from the default 8x8 font
            c=0x00;
            bit1=((BasicFont[C-32][i])>>j)  & 0x01;  
            bit2=((BasicFont[C-32][i+1])>>j) & 0x01;
           // Each bit is changed to a nibble
            c|=(bit1)?grayH:0x00;
            c|=(bit2)?grayL:0x00;
            OLED_WR_Byte(c,OLED_DATA);
        }
    }
}

//******************************************************************
//��������  OLED_put_String
    
    
//���ܣ�    ��ʾ�ַ���
//���������String������ʾ���ַ���
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void OLED_put_String(const char *String)
{
    unsigned char i=0;
    while(String[i])
    {
        OLED_put_Char(String[i]);     
        i++;
    }
}

//******************************************************************
//��������  OLED_disp_pic_BMP
    
    
//���ܣ�    ��ʾBMP��ɫͼƬ
//���������x,y������ʾ��BMPͼƬ��ʼ����
//          pic������ʾ��BMPͼƬ����������ָ��
//          value���Ҷ�ֵ
//          len������ʾ��BMPͼƬ���������鳤��
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void OLED_disp_pic_BMP(uint8_t x, uint8_t y,const unsigned char *pic,char value,uint32_t len)
{ 
	uint32_t i=0,k=0,address=0;
	for(k=0;k<16;k++)
	{
		for(i = 0; i < 64; i++) 
		{		
			OLED_Set_Pos(k*8+y,i+x);
			//transfer_col_data(gImage_21[address],gImage_21[address+1]); 
			OLED_transfer_col_data2(pic[address],pic[address+1],value);  
			address+=2;
			if(address>=len)
			{
				return;
			}
		}
	}
}	

//******************************************************************
//��������  OLED_modify_num
//���ܣ�    �޸�UI������ʾ������
//���������x,y�����޸ĵ���������
//          num�����޸ĵ�����ֵ
//          type�����ִ�С
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void OLED_modify_num(uint8_t x, uint8_t y,uint32_t num,uint8_t type)
{
	char buf[32]= {0};
	sprintf(buf,"%d",num);
	if(type == 8)
	{
		OLED_display_string_5x8(x,y,0,(uint8_t *)buf);
	}
	else if(type == 16)
	{
		OLED_display_string_8x16(x,y,(uint8_t *)buf);
	}
	else if(type == 24)
	{
		OLED_display_string_12x24(x,y,(uint8_t *)buf);
	}
	else if(type == 32)
	{
			OLED_display_string_16x32(x,y,(uint8_t *)buf);
	}
}

//******************************************************************
//��������  OLED_show_run_page
    
    
//���ܣ�    ��ʾUI����
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void OLED_show_run_page(void)
{
		OLED_draw_line(5, 37, 59, 37);
		OLED_draw_line(5, 84, 59, 84);
		OLED_draw_line(25, 38, 25, 83);
		OLED_display_string_5x8(7,20,0,"DEPTH");
		OLED_display_string_16x32(30,5,"100");
		OLED_display_string_5x8(54,20,0,"ft");
		OLED_display_string_12x24(6,54,"25");
		OLED_display_string_5x8(18,58,0,"18");
		OLED_display_string_5x8(28,48,0,"NEXT");
		OLED_display_string_5x8(47,48,0,"STOP");
		OLED_display_string_8x16(27,59,"115");
	//	OLED_display_string_5x8(38,64,0,"ft");
		OLED_disp_string_8x16_16x16(44,59,"3:10");
		OLED_display_string_5x8(7,95,0,"CCVME");
		OLED_display_string_5x8(36,95,0,"NDL");
		OLED_display_string_5x8(50,95,0,"TTS");
		OLED_disp_string_8x16_16x16(7,105,"CC 18");
		OLED_disp_string_8x16_16x16(38,105,"0");
		OLED_disp_string_8x16_16x16(48,105,"148");
}
