//---------------------------------------------------------------
//MCU I / O PORT 
//---------------------------------------------------------------
#define LED_7SEG_A								RA0//output
#define LED_7SEG_B								RA1//output
#define LED_7SEG_C								RA2//output
#define LED_7SEG_D								RA3//output
#define LED_7SEG_E								RA4//output
#define LED_7SEG_F								RA5//output
//-----------------------------------------------------
#define GDO0_DIO									RB0
#define GD02_DCLK									RB1
#define CC2500_EM_CSN							RB2//output
#define CC1100_EM_CSN							RB2//output
#define LED_7SEG_G								RB3//output
#define USB_EN										RB4//output
#define Function_all_button				RB5//input
#define LED1											RB6//outut
#define LED2											RB7//output
//-----------------------------------------------------
#define S2												RC0//input
#define S3												RC1//input
#define S4												RC2//input
#define S5												RC3//input
#define MOSI											RC4//output
#define buzzer										RC5//output
#define SCLK											RC6//output
#define MISO											RC7//input
//-----------------------------------------------------
#define LCD_E											RD0//output
#define LCD_RS										RD1//output
#define LCD_RW										RD2//output
#define CC2500_module_CSN					RD3//output
#define USB_data0									RD4//input
#define USB_data1									RD5//input
#define USB_data2									RD6//input
#define USB_data3									RD7//input
//-----------------------------------------------------
#define JP4												RE0//input
#define JP4_TRIS									TRISE0
#define JP3												RE1//input
#define JP3_TRIS									TRISE1
#define	JP2												RE2//input
#define JP2_TRIS									TRISE2
#define MCU_reset									RE3//input
#define CC1020_EM_PSEL						RE4//output
#define CC1100_module_CSN					RE5//output
#define LCD_back_ligth						RE6//output
#define S1												RE7//input
//-----------------------------------------------------
#define keypad_right_button2			RG5//output
#define keypad_3_button1					RF0//output
#define keypad_2_return						RF1//output
#define keypad_1_backspace				RF2//output
#define keypad_0_enter						RF3//output
#define LCD_D4										RF4//output
#define LCD_D5										RF5//output
#define LCD_D6										RF6//output
#define LCD_D7										RF7//output
//-----------------------------------------------------
#define keypad_enter							RG0//input
#define keypad_backspace					RG0
#define keypad_return							RG0
#define keypad_button1						RG0
#define keypad_button2						RG0
#define keypad_C									RG1//input
#define keypad_D									RG1
#define keypad_E									RG1
#define keypad_F									RG1
#define keypad_up									RG1
#define keypad_8									RG2//input
#define keypad_9									RG2
#define keypad_A									RG2
#define keypad_B									RG2
#define keypad_down								RG2
#define keypad_4									RG3//input
#define keypad_5									RG3
#define keypad_6									RG3
#define keypad_7									RG3
#define keypad_left								RG3
#define keypad_0									RG4//input
#define keypad_1									RG4
#define keypad_2									RG4
#define keypad_3									RG4
#define keypad_right							RG4
//---------------------------------------------------------------
//
//---------------------------------------------------------------
static volatile unsigned char INDF	@ 0x000;
#define FBuzzer_Enable()						buzzer=1
#define FBuzzer_Disable()						buzzer=0
#define FTimer1_Enable()						TMR1ON=1
#define FTimer1_Disable()						TMR1ON=0
#define TIME_H_BYTE_4M							(65535-4000)>>8	/* Timer1 4ms for 4M crystal*/
#define TIME_L_BYTE_4M							(65535-4000)
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FDelay_4us(unsigned char Bdly)
{
	Bdelay_us=Bdly;
	do{
		NOP();
		Bdelay_us--;
	}while(Bdelay_us);
	CLRWDT();
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FDelay_ms(unsigned char Bdly)
{
	Bdelay_ms=Bdly;
	do{
		Bdelay_us=250;
		do{
			NOP();
			Bdelay_us--;
		}while(Bdelay_us);
		Bdelay_ms--;
	}while(Bdelay_ms);
	CLRWDT();
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FMCU_clear_all_ram(void)
{
	for(FSR=0x20;FSR<0x80;FSR++){IRP=1;INDF=0;IRP=0;INDF=0;}
	for(FSR=0xA0;FSR<0xF0;FSR++){IRP=1;INDF=0;IRP=0;INDF=0;}
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FMCU_Initial(void)
{
	PORTA=0b11111111;
	PORTB=0b11101111;
	PORTC=0b10001111;
	PORTD=0b11111111;
	PORTE=0b11111111;
	INTCON=0b11000000;
	PIR1=0b00000000;
	PIR2=0b00000000;
	T1CON=0b00000000;
	T2CON=0b00000000;
	RCSTA=0b00000000;
	SSPCON=0b00000000;
	CCP1CON=0b00000000;
	CCP2CON=0b00000000;
	TRISA=0b11000000;
	TRISB=0b00100011;
	TRISC=0b10001111;
	TRISD=0b11110000;
	TRISE=0b10001111;
	SSPSTAT=0b01000000;
	OPTION=0b01001111;
	PIE1=0b00000001;
	PIE2=0b00000000;
	IOCB=0b00000000;
	WPUB=0b00100011;
	OSCCON=0b01100001;
	OSCTUNE=0b00000000;
	CMCON0=0b00000111;
	VRCON=0b00000000;
	TXSTA=0b00000000;
	ANSEL=0b00000000;
	SSPSTAT=0b01000000;
	LCDCON=0b01000000;
	LVDCON=0b00000000;
	LCDSE0=0b00000000;
	LCDSE1=0b00000000;
	LCDSE2=0b00000000;
	LCDSE3=0b00000000;
	LCDSE4=0b00000000;
	LCDSE5=0b00000000;
	PORTF=0b00001111;
	TRISF=0b00000000;
	PORTG=0b00111111;
	TRISG=0b00011111;
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
#define CEnter			0x10
#define CBackspace	0x20
#define CReturn			0x30
#define CButton1		0x40
#define CButton2		0x50
#define CUp					0x60
#define CDown				0x70
#define CLeft				0x80
#define CRight			0x90
#define CError			0xFF
#define C0					0x00
#define C1					0x01
#define C2					0x02
#define	C3					0x03
#define C4					0x04
#define C5					0x05
#define C6					0x06
#define C7					0x07
#define C8					0x08
#define C9					0x09
#define CA					0x0A
#define CB					0x0B
#define CC					0x0C
#define CD					0x0D
#define CE					0x0E
#define CF					0x0F
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FLED_7SEG_Output(unsigned char Bp_w_data)
{
	Btemp1=Bp_w_data;
	switch(Btemp1)
	{
		case 0x00:
			LED_7SEG_A=0;
			LED_7SEG_B=0;
			LED_7SEG_C=0;
			LED_7SEG_D=0;
			LED_7SEG_E=0;
			LED_7SEG_F=0;
			LED_7SEG_G=1;
		break;
		case 0x01:
			LED_7SEG_A=1;
			LED_7SEG_B=0;
			LED_7SEG_C=0;
			LED_7SEG_D=1;
			LED_7SEG_E=1;
			LED_7SEG_F=1;
			LED_7SEG_G=1;
		break;
		case 0x02:
			LED_7SEG_A=0;
			LED_7SEG_B=0;
			LED_7SEG_C=1;
			LED_7SEG_D=0;
			LED_7SEG_E=0;
			LED_7SEG_F=1;
			LED_7SEG_G=0;
		break;
		case 0x03:
			LED_7SEG_A=0;
			LED_7SEG_B=0;
			LED_7SEG_C=0;
			LED_7SEG_D=0;
			LED_7SEG_E=1;
			LED_7SEG_F=1;
			LED_7SEG_G=0;
		break;
		case 0x04:
			LED_7SEG_A=1;
			LED_7SEG_B=0;
			LED_7SEG_C=0;
			LED_7SEG_D=1;
			LED_7SEG_E=1;
			LED_7SEG_F=0;
			LED_7SEG_G=0;
		break;
		case 0x05:
			LED_7SEG_A=0;
			LED_7SEG_B=1;
			LED_7SEG_C=0;
			LED_7SEG_D=0;
			LED_7SEG_E=1;
			LED_7SEG_F=0;
			LED_7SEG_G=0;
		break;
		case 0x06:
			LED_7SEG_A=0;
			LED_7SEG_B=1;
			LED_7SEG_C=0;
			LED_7SEG_D=0;
			LED_7SEG_E=0;
			LED_7SEG_F=0;
			LED_7SEG_G=0;
		break;
		case 0x07:
			LED_7SEG_A=0;
			LED_7SEG_B=0;
			LED_7SEG_C=0;
			LED_7SEG_D=1;
			LED_7SEG_E=1;
			LED_7SEG_F=1;
			LED_7SEG_G=1;
		break;
		case 0x08:
			LED_7SEG_A=0;
			LED_7SEG_B=0;
			LED_7SEG_C=0;
			LED_7SEG_D=0;
			LED_7SEG_E=0;
			LED_7SEG_F=0;
			LED_7SEG_G=0;
		break;
		case 0x09:
			LED_7SEG_A=0;
			LED_7SEG_B=0;
			LED_7SEG_C=0;
			LED_7SEG_D=0;
			LED_7SEG_E=1;
			LED_7SEG_F=0;
			LED_7SEG_G=0;
		break;
		case 0x0A:
			LED_7SEG_A=0;
			LED_7SEG_B=0;
			LED_7SEG_C=0;
			LED_7SEG_D=1;
			LED_7SEG_E=0;
			LED_7SEG_F=0;
			LED_7SEG_G=0;
		break;
		case 0x0B:
			LED_7SEG_A=1;
			LED_7SEG_B=1;
			LED_7SEG_C=0;
			LED_7SEG_D=0;
			LED_7SEG_E=0;
			LED_7SEG_F=0;
			LED_7SEG_G=0;
		break;
		case 0x0C:
			LED_7SEG_A=0;
			LED_7SEG_B=1;
			LED_7SEG_C=1;
			LED_7SEG_D=0;
			LED_7SEG_E=0;
			LED_7SEG_F=0;
			LED_7SEG_G=1;
		break;
		case 0x0D:
			LED_7SEG_A=1;
			LED_7SEG_B=0;
			LED_7SEG_C=0;
			LED_7SEG_D=0;
			LED_7SEG_E=0;
			LED_7SEG_F=1;
			LED_7SEG_G=0;
		break;
		case 0x0E:
			LED_7SEG_A=0;
			LED_7SEG_B=1;
			LED_7SEG_C=1;
			LED_7SEG_D=0;
			LED_7SEG_E=0;
			LED_7SEG_F=0;
			LED_7SEG_G=0;
		break;
		case 0x0F:
			LED_7SEG_A=0;
			LED_7SEG_B=1;
			LED_7SEG_C=1;
			LED_7SEG_D=1;
			LED_7SEG_E=0;
			LED_7SEG_F=0;
			LED_7SEG_G=0;
		break;
		default:
			LED_7SEG_A=1;
			LED_7SEG_B=1;
			LED_7SEG_C=1;
			LED_7SEG_D=1;
			LED_7SEG_E=1;
			LED_7SEG_F=1;
			LED_7SEG_G=1;
		break;
	}
}
