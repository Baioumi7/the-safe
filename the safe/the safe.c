#define  F_CPU 8000000UL
#include <util/delay.h>
#include "keypad_driver.h"
#include "LCD.h"
#define  EEPROM_STATUS_LOCATION 0x20
#define  EEPROM_PASSWORD_LOCATION1 0x21
#define  EEPROM_PASSWORD_LOCATION2 0x22
#define  EEPROM_PASSWORD_LOCATION3 0x23
#define  EEPROM_PASSWORD_LOCATION4 0x24
#define MAX_TRIES 2

char arr[4];
int main(void)
{
	char value=NOTPRESSED;
	char flag=0,i;
	char tries=MAX_TRIES;
	keypad_vInit();
	LCD_vInit();
	if (EEPROM_read(EEPROM_STATUS_LOCATION)==NOTPRESSED)
	{
		LCD_vSend_string("set pass:");
		for (i=0;i<=3;i++)
		{
			do 
			{
				value=keypad_u8check_press();
			}while (value==NOTPRESSED);
			LCD_vSend_char(value);
			_delay_ms(500);
			LCD_movecursor(1,10+i);
			LCD_vSend_char('*');
			_delay_ms(500);
			EEPROM_write(EEPROM_PASSWORD_LOCATION1+i,value);
		}	
		EEPROM_write(EEPROM_STATUS_LOCATION,0x00);
	}				
    while(flag==0)
    {
		arr[0]=arr[1]=arr[2]=arr[3]=NOTPRESSED;
		LCD_clearscreen();
		LCD_vSend_string("check pass:");
		for (i=0;i<=3;i++)
		{
			do
			{
				arr[i]=keypad_u8check_press();
			}while (arr[i]==NOTPRESSED);
			LCD_vSend_char(arr[i]);
			_delay_ms(500);
			LCD_movecursor(1,12+i);
			LCD_vSend_char('*');
			_delay_ms(500);
		}		
		
	if(EEPROM_read(EEPROM_PASSWORD_LOCATION1)==arr[0] &&  EEPROM_read(EEPROM_PASSWORD_LOCATION2)==arr[1] && EEPROM_read(EEPROM_PASSWORD_LOCATION3)==arr[2] && EEPROM_read(EEPROM_PASSWORD_LOCATION4)==arr[3])
	{
		LCD_clearscreen();
		LCD_vSend_string("right password");
		LCD_movecursor(2,1);
		LCD_vSend_string("safe opened");
		flag=1;
	}	
	else
	{
		tries=tries-1;
		if (tries>0)
		{
			LCD_clearscreen();
			LCD_vSend_string("wrong password");
			_delay_ms(1000);
			LCD_clearscreen();
			LCD_vSend_string("tries left:");
			LCD_vSend_char(tries+48);
			_delay_ms(1000);
		
		}
		else
		{
			LCD_clearscreen();
			LCD_vSend_string("wrong password");
			LCD_movecursor(2,1);
			LCD_vSend_string("safe closed");
			flag=1;
		}
	}
	}			
}


