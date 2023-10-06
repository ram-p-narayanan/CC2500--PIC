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


void PIC_Clear_Ram_Reg(void)
{
	for(FSR = 0x20;FSR < 0x80;FSR++){IRP = 1;INDF = 0;IRP = 0;INDF = 0;}
	for(FSR = 0xA0;FSR < 0xF0;FSR++){IRP = 1;INDF = 0;IRP = 0;INDF = 0;}
	for(FSR = 0x120;FSR < 0x170;FSR++){IRP = 1;INDF = 0;IRP = 0;INDF = 0;}
	for(FSR = 0x1A0;FSR < 0x1F0;FSR++){IRP = 1;INDF = 0;IRP = 0;INDF = 0;}
}

void PIC_Register_Initialize(void)
{
/* Initialize necessary PIC registers here. Changes has not been made to the ports and TRIS.. */
	PORTA=0b11111111;     // check it
	PORTB=0b11101111;		// check it
	PORTC=0b10001111;		// check it
	PORTD=0b11111111;		// check it
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

