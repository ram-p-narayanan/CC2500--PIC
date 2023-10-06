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
#define DataBytes_Tx_Rx						20

#define CC2500_Clear_TX_FIFO()					Write_Command_in_CC2500(SFTX)
#define CC2500_Clear_RX_FIFO()					Write_Command_in_CC2500(SFRX)
#define CC2500_Frequency_Calibration()	        Write_Command_in_CC2500(SCAL)
#define CC2500_Transmit_Mode()					Write_Command_in_CC2500(STX)
#define CC2500_Receive_Mode()					Write_Command_in_CC2500(SRX)
#define CC2500_Get_Status()					    Write_Command_in_CC2500(SNOP)

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

#define CC2500_Chip_Ready						Status_byte.bits.bit7
#define CC2500_Chip_State0						Status_byte.bits.bit6
#define CC2500_Chip_State1						Status_byte.bits.bit5
#define CC2500_Chip_State2						Status_byte.bits.bit4
#define CC2500_Chip_FIFO_Bytes_Available0		Status_byte.bits.bit3
#define CC2500_Chip_FIFO_Bytes_Available1		Status_byte.bits.bit2
#define CC2500_Chip_FIFO_Bytes_Available2		Status_byte.bits.bit1
#define CC2500_Chip_FIFO_Bytes_Available3		Status_byte.bits.bit0

void PIC_Clear_Ram_Reg(void)
{
	for(FSR = 0x20;FSR < 0x80;FSR++){IRP = 1;INDF = 0;IRP = 0;INDF = 0;}
	for(FSR = 0xA0;FSR < 0xF0;FSR++){IRP = 1;INDF = 0;IRP = 0;INDF = 0;}
	for(FSR = 0x120;FSR < 0x170;FSR++){IRP = 1;INDF = 0;IRP = 0;INDF = 0;}
	for(FSR = 0x1A0;FSR < 0x1F0;FSR++){IRP = 1;INDF = 0;IRP = 0;INDF = 0;}
}

void PIC_Register_Initialize(void)
{
/* Number of Pins to be used for interfacing the PIC with CC2500. 

						CSn/SS  -------->   Pin RC2 ----> To be Set as Output Pin
						SCLK    -------->   Pin RC3 ----> To be Set as Output Pin
						MOSI    -------->   Pin RC5 ----> To be Set as Output Pin
						MISO    -------->   Pin RC4 ----> To be Set as Input  Pin     */

/* Number of pins to be used for displaying data on Serial Port 

						UART Rx -------->  Pin RC7  ------>  To be Set as Input  Pin  
						UART Tx -------->  Pin RC6  ------>  To be Set as Output Pin    */
  
 
 PORTC 				= 0b00000000;
 TRISC 				= 0b10011100;
 SPI_Control_Reg 	= 0b00000000;
 SSPSTAT 			= 0b01000000;
 INTCON	 			= 0b00000000;
 PIR1 				= 0b00000000;
 PIR2 				= 0b00000000;
 PIE1 				= 0b00000000;
 PIE2 				= 0b00000000;
 RCSTA 				= 0b10000000;
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

