
#include <REGX51.H>
#include <ThuvienLCd.h>
#include <Real_Time_DS1307.H>

unsigned char slave1 = 0X7E;
unsigned int hour, minute, second;
unsigned int day, date, month, year;
sbit thaydoithoigian = P1^1; // R5 -> P1.1 -> Mode/Select
sbit tang  = P1^4; // R8 -> P1.4 -> Tang (+)
sbit giam  = P1^7; // R6 -> P1.7 -> Giam (-)
sbit thaydoichedo = P1^6; // R9
sbit chonchedo = P1^0;
#define Buzz P3_0




unsigned char gio = 0;    // Bien luu tru gio
unsigned char phut = 0;   // Bien luu tru phut
unsigned char giay = 0;   // Bien luu tru giay
unsigned char mode = 0;   // Bien luu che do hoat dong
                          // 0: Hien thi binh thuong
unsigned char ngay = 0;
unsigned char thang = 0;
unsigned char nam = 0;
unsigned char mode1 = 1;                          // 1: Chinh Gio
                        // 2: Chinh Phut
                        // 3: Chinh Giay


int dem1=0;

void delay(long time)
{
	time = time * 25;
	while(time--) {}
}

void main(void)
{	
	Buzz = 0;
	//DS1307_Init();
	
	LCD_Slave(slave1);
	LCD_Init();

	
	LCD_Gotoxy(1,1); // cot dau tien - hang dau tien
	LCD_Send_String("KTMT");
	LCD_Gotoxy(1,2); // cot dau tien - hang dau tien
	LCD_Send_String("NHOM @@@@");
	delay_ms(10);
	
	LCD_Clear();
	DS1307_Init();
	
	while(1){
		if(thaydoichedo == 0)
    {
			 mode = !mode;
			 //while(thaydoichedo == 0)
			 LCD_Clear();
     }
		if(mode == 0){
				LCD_Slave(slave1);
				DS1307_Read_Time(&hour, &minute, &second);
				LCD_Gotoxy(1,1); // cot dau tien - hang dau tien
				LCD_Send_String("TIME: ");
				if(hour < 10) LCD_Send_Data('0');
				LCD_Send_Number(hour);
				LCD_Send_Data(':');
				if(minute < 10) LCD_Send_Data('0');
				LCD_Send_Number(minute);
				LCD_Send_Data(':');
				if(second < 10) LCD_Send_Data('0');
				LCD_Send_Number(second);
				
				
				DS1307_Read_Date(&day, &date, &month, &year);
				LCD_Gotoxy(1,2); // cot dau tien - hang dau tien
				LCD_Send_String("DATE: ");
				if(date < 10) LCD_Send_Data('0');
				LCD_Send_Number(date);
				LCD_Send_Data('/');
				if(month < 10) LCD_Send_Data('0');
				LCD_Send_Number(month);
				LCD_Send_Data('/');
				LCD_Send_Number(year + 2000);  // neu year = 22 thì in ra 2022
				
				
				if(hour == gio && minute == phut && second == giay){
					Buzz = 1; delay_ms(250); Buzz = 0; delay_ms(250);
					Buzz = 1; delay_ms(250); Buzz = 0; delay_ms(250);
					Buzz = 1; delay_ms(250); Buzz = 0; delay_ms(250);
					Buzz = 1; delay_ms(250); Buzz = 0; delay_ms(250);
				}
	
		}
		else{
			LCD_Gotoxy(1,1); // cot dau tien - hang dau tien
			LCD_Send_String("ALARM ");
			LCD_Gotoxy(1,2); // cot dau tien - hang dau tien
			if(gio < 10) LCD_Send_Data('0');
			LCD_Send_Number(gio);
			LCD_Send_Data(':');
			if(phut < 10) LCD_Send_Data('0');
			LCD_Send_Number(phut);
			LCD_Send_Data(':');
			if(giay < 10) LCD_Send_Data('0');
			LCD_Send_Number(giay);
			
			
			
			
			if(thaydoithoigian == 0)
			{
        //delay_ms(1);
        mode1++;
        //while(thaydoithoigian == 0);
       }

      // Nút tang
      if(tang == 0)
      {
         //delay_ms(1);
         if(mode1 % 3 == 1) {
            gio++;
						if(gio > 23) gio = 0;
          } else if(mode1 % 3 == 2){
            phut++;
            if(phut > 59) phut = 0;
          }
					else{
						giay++;
						if(giay>59) giay = 0;
					}
			
          //while(tang == 0){;}

       }
       // Nút giam
			if(giam == 0)
      {
				//delay_ms(1);
				if(mode1 % 3 == 1) {
					 if(gio == 0) gio = 23;
					 else gio--;
				} else if(mode1 % 3 == 2){
					if(phut == 0) phut = 59;
					else phut--;
				}
				else{
						if(giay == 0) giay = 59;
						else giay--;
					}
					
					//while(giam == 0){;}
      }
                    
				
		}
		
	}
	

	LCD_Clear();		
}


