//===============================================================
//PIC16LF73
//===============================================================
#include <pic.h>
#include "Chipcon.h"
//===============================================================
//Global Definitions
//===============================================================
#define Enable	1
#define Disable	0

#define CC2500_module_CSn					RC2      //output
#define SCLK 								RC3
#define MISO 								RC4
#define MOSI 								RC5

#define SPI_Control_Reg						SSPCON
#define SPI_Buffer_Reg						SSPBUF
#define SPI_Interrupt_Flag_Bit				SSPIF
#define SPI_Buffer_Full_Bit				    BF


#define CC2500_Clear_TX_FIFO()					Write_Command_in_CC2500(SFTX)
#define CC2500_Clear_RX_FIFO()					Write_Command_in_CC2500(SFRX)
#define CC2500_Frequency_Calibration()	        Write_Command_in_CC2500(SCAL)
#define CC2500_Transmit_Mode()					Write_Command_in_CC2500(STX)

#define Tx_Function_cc2500
#define Rx_Function_cc2500

//===============================================================
//Global variable Declarations
//===============================================================
unsigned char Loop_Variable;
unsigned char Temp1;
unsigned char Buffer_Data;
unsigned char Temp_data = 0x85;
unsigned char Receiver_Data;
unsigned char delay_Time_uS;
unsigned char delay_Time_mS;
//===============================================================
//Function Declarations start here
//===============================================================
void Delay_mS(unsigned char delay_Time_mS)
{
	do{
		delay_Time_uS = 250;
		do{
			delay_Time_uS--;
		}while(delay_Time_uS);
		delay_Time_mS--;
	}while(delay_Time_mS);
}

void Delay_uS(unsigned char delay_Time_uS)
{
	do{
		NOP();
		delay_Time_uS--;
	}while(delay_Time_uS);
}

void PIC_Clear_Ram_Reg(void)
{
	for(FSR = 0x20;FSR < 0x80;FSR++){IRP = 1;INDF = 0;IRP = 0;INDF = 0;}
	for(FSR = 0xA0;FSR < 0xF0;FSR++){IRP = 1;INDF = 0;IRP = 0;INDF = 0;}
	for(FSR = 0x120;FSR < 0x170;FSR++){IRP = 1;INDF = 0;IRP = 0;INDF = 0;}
	for(FSR = 0x1A0;FSR < 0x1F0;FSR++){IRP = 1;INDF = 0;IRP = 0;INDF = 0;}
}

void PIC_Register_Initialize(void)
{
/* Initialize necessary PIC registers here. */
}

void CC2500_Module_Reset(void)
{
	CC2500_module_CSn = 1;
	NOP();
	SCLK = 0;
	NOP();
	MOSI = 0;
	NOP();
	CC2500_module_CSn = 0;
	Write_Command_in_CC2500(SIDLE);
	/* CC2500_module_CSn = 1;
	Delay_uS(5);
	CC2500_module_CSn = 0;
	Delay_uS(5);
	CC2500_module_CSn = 1;
	Delay_uS(5);
	CC2500_module_CSn = 0;
	Buffer_Data = SRES;
	while(MISO == 1);
	SPI_Control_Reg = 0x20;
	Write_Byte_in_CC2500();
	SPI_Control_Reg = 0x00;
	while(MISO == 1);
	CC2500_module_CSn = 1;
	Delay_uS(1); */
}

void Write_Command_in_CC2500(unsigned char CC2500_Command)
{
	CC2500_module_CSn = 0;
	Buffer_Data = CC2500_Command;
	while(MISO == 1);
	SPI_Control_Reg = 0x20;
	Write_Byte_in_CC2500();
	SPI_Control_Reg = 0x00;
	//CC2500_module_CSn = 1;
}

void Write_Byte_in_CC2500(void)
{
	SPI_Buffer_Reg = Buffer_Data;
	while(SPI_Interrupt_Flag_Bit == 0);
	SPI_Interrupt_Flag_Bit = 0;
	while(SPI_Buffer_Full_Bit == 0);
}

unsigned char Read_Byte_from_CC2500(void)
{
	SPI_Buffer_Reg=0x00;
	while(SPI_Interrupt_Flag_Bit==0);
	SPI_Interrupt_Flag_Bit=0;
	while(SPI_Buffer_Full_Bit==0);
	Receiver_Data = SPI_Buffer_Reg;
	return (Receiver_Data);
}

void Write_registers_in_CC2500(unsigned char CC2500_Address,unsigned char CC2500_Data)
{
	CC2500_module_CSn = 0;
	Buffer_Data = CC2500_Address;
	while(MISO == 1);
	SPI_Control_Reg = 0x20;
	Write_Byte_in_CC2500();
	Buffer_Data = CC2500_Data;
	Write_Byte_in_CC2500();
	//CC2500_module_CSn = 1;
	SPI_Control_Reg = 0x00;
}
void CC2500_Initial_all_registers(void)
{
	unsigned char Loop_Variable;
	for(Loop_Variable = 0;Loop_Variable < 0x2F;Loop_Variable++)  // The register address in a CC2500 module starts
															     //	at 00 and goes up to 0x2F.  
	{
		Temp1 = CC2500_rfSettings[Loop_Variable];
		Write_registers_in_CC2500(Loop_Variable,Temp1);
	}
}

void Read_Status_Register_from_CC2500(unsigned char Bp_w_address)
{
	CC2500_module_CSn = 0;
	Buffer_Data = Bp_w_address + 0xC0;
	while(MISO == 1);
	SSPCON = 0x20;
	Write_Byte_in_CC2500();
	Read_Byte_from_CC2500();
	//CC2500_module_CSn = 1;
	SSPCON = 0x00;
}

//===============================================================
// Main Routine Starts here
//===============================================================
void main(void)
{
#if Tx_Function_cc2500
	Delay_mS(50);
	PIC_Clear_Ram_Reg();	
	PIC_Register_Initialize();
	CC2500_Module_Reset();
	CC2500_Initial_all_registers();
	//CC2500_PA_Table();
	CC2500_Clear_TX_FIFO();
	CC2500_Clear_RX_FIFO();
	CC2500_Frequency_Calibration();
	Delay_uS(200);
	//CC2500_Transmit_Mode();
	//while(1)
	//{
		CC2500_module_CSn = 0;
		Delay_uS(2);   
		Buffer_Data = TXFIFO;
		while(MISO == 1);
		SPI_Control_Reg = 0x20;
		Write_Byte_in_CC2500();
		Buffer_Data = Temp_data;
		while(MISO == 1);
		Write_Byte_in_CC2500();
		Receiver_Data = SPI_Buffer_Reg;
		SPI_Control_Reg = 0x00;
		Read_Status_Register_from_CC2500(TXFIFO);
		//SPI_Control_Reg = 0x00;
	//}
#endif
}