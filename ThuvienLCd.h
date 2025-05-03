
void i2c_start(void);
void i2c_stop(void);
void i2c_ACK(void);
void i2c_write(unsigned char);
void i2c_DevWrite(unsigned char);
void lcd_send_cmd(unsigned char);
void LCD_Send_Data(unsigned char);
void LCD_Send_String(unsigned char *p);
void LCD_Slave(unsigned char slave);
void delay_ms(unsigned int);
void LCD_Init();
void LCD_Gotoxy (int col, int row);
void LCD_Send_Number(int number);






void LCD_Clear();