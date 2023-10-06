
// PIC16F73 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bit (Code protection off)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)




#define Enable                                  1
#define Disable                                 0

#define CC2500_module_CSn			RC2      //output
#define SCLK 					RC3
#define MISO 					RC4
#define MOSI 					RC5

#define SPI_Control_Reg				SSPCON
#define SPI_Status_Reg				SSPSTAT
#define SPI_Buffer_Reg				SSPBUF
#define SPI_Interrupt_Flag_Bit			SSPIF
#define SPI_Buffer_Full_Bit			BF
#define DataBytes_Tx_Rx				20

#define CC2500_Clear_TX_FIFO()			Write_Command_in_CC2500(SFTX)
#define CC2500_Clear_RX_FIFO()			Write_Command_in_CC2500(SFRX)
#define CC2500_Frequency_Calibration()	        Write_Command_in_CC2500(SCAL)
#define CC2500_Transmit_Mode()			Write_Command_in_CC2500(STX)
#define CC2500_Get_Status()		        Write_Command_in_CC2500(SNOP)
#define CC2500_Idle_Status()                    Write_Command_in_CC2500(SIDLE)



union{
	unsigned char byte;
	struct{
		unsigned char bit0:1;
		unsigned char bit1:1;
		unsigned char bit2:1;
		unsigned char bit3:1;
		unsigned char bit4:1;
		unsigned char bit5:1;
		unsigned char bit6:1;
		unsigned char bit7:1;
	}bits;
}Status_byte;

#define CC2500_Chip_Ready				Status_byte.bits.bit7
#define CC2500_Chip_State0				Status_byte.bits.bit6
#define CC2500_Chip_State1				Status_byte.bits.bit5
#define CC2500_Chip_State2				Status_byte.bits.bit4
#define CC2500_Chip_FIFO_Bytes_Available0		Status_byte.bits.bit3
#define CC2500_Chip_FIFO_Bytes_Available1		Status_byte.bits.bit2
#define CC2500_Chip_FIFO_Bytes_Available2		Status_byte.bits.bit1
#define CC2500_Chip_FIFO_Bytes_Available3		Status_byte.bits.bit0

void Delay_mS(unsigned char delay_Time_mS);
void Delay_uS(unsigned char delay_Time_uS);
void PIC_Clear_Ram_Reg(void);
void PIC_Register_Initialize(void);
void CC2500_Module_Reset(void);
void CC2500_Initialize_all_registers(void);
void Write_Command_in_CC2500(unsigned char CC2500_Command);
void Write_Byte_in_CC2500(void);
unsigned char Read_Byte_from_CC2500(void);
void Write_registers_in_CC2500(unsigned char CC2500_Address,unsigned char CC2500_Data);



unsigned char delay_Time_uS;
unsigned char delay_Time_mS;





