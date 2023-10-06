//===============================================================
//PIC16LF73
//===============================================================
#include <pic.h>
#include "Chipcon.h"
#include "BytesTx_Display.h"
//===============================================================
//Global Definitions
//===============================================================

#define Tx_Function_cc2500
#define Rx_Function_cc2500

//===============================================================
//Global variable Declarations
//===============================================================
static unsigned char Loop_Count;
static unsigned char Temp1;
static unsigned char Buffer_Data, SizeOfTxData;
unsigned char Temp_data[DataBytes_Tx_Rx] = "TiinoResearchLabs\n\r";
const char *ptr;
static unsigned char Receiver_Data, Receiver_Data_Duplicate;
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
//	for(FSR = 0x120;FSR < 0x170;FSR++){IRP = 1;INDF = 0;IRP = 0;INDF = 0;}
//	for(FSR = 0x1A0;FSR < 0x1F0;FSR++){IRP = 1;INDF = 0;IRP = 0;INDF = 0;}
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
 
 SPI_Control_Reg 	       |= 0b00000000;
 SPI_Status_Reg		       |= 0b01000000;
 SPI_Control_Reg 	       |= 0b00000010; // Fosc/64
 INTCON	 			= 0b00000000;
 PIR1 				= 0b00000000;
 PIR2 				= 0b00000000;
 PIE1 				= 0b00000000;
 PIE2 				= 0b00000000;
// RCSTA 				= 0b10000000;
 TRISCbits.TRISC4               = Enable;
 TRISCbits.TRISC5               = Disable;
 TRISCbits.TRISC3               = Disable;
 TRISCbits.TRISC2               = Disable;

 PORTCbits.RC2                  = Enable;
 NOP();
 
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

void CC2500_Initialize_all_registers(void)
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
	SSPEN = 1;
	Write_Byte_in_CC2500();
	
	//CC2500_module_CSn = 1;
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
        SSPEN = Enable;
	Write_Byte_in_CC2500();
	Buffer_Data = CC2500_Data;
	Write_Byte_in_CC2500();
	CC2500_module_CSn = 1;
	
}

void Write_Byte_in_CC2500(void)
{
	SPI_Buffer_Reg = Buffer_Data;
	while(SPI_Interrupt_Flag_Bit == 0);
	SPI_Interrupt_Flag_Bit = 0;
	while(SPI_Buffer_Full_Bit == 0);
}


void main(void)
{

	//#if Tx_Function_cc2500
		Delay_mS(50);
		PIC_Clear_Ram_Reg();	
		PIC_Register_Initialize();
		CC2500_Module_Reset();
		CC2500_Initialize_all_registers();
		//CC2500_PA_Table();
		
		Delay_uS(200);
while(1){	
		CC2500_module_CSn = 0;
                Delay_uS(5);
                CC2500_Clear_TX_FIFO();
		CC2500_Clear_RX_FIFO();
                CC2500_Idle_Status();
		CC2500_Frequency_Calibration();
                CC2500_Get_Status();
                NOP(); NOP(); while(!SPI_Buffer_Full_Bit);
		Receiver_Data = SPI_Buffer_Reg;
		Receiver_Data_Duplicate = Receiver_Data;
		Receiver_Data_Duplicate &= 0x70;

                switch (Receiver_Data_Duplicate)
                {
                    case (0):
                        SizeOfTxData = sizeof(Temp_data);
                        Write_Command_in_CC2500(TXFIFO_Burst);
                        for (Loop_Count = 0; Loop_Count <= SizeOfTxData; Loop_Count++)
                        {
                            while(Temp_data[Loop_Count] != '\0')
                            {
                                Buffer_Data = Temp_data[Loop_Count];
                                Write_Byte_in_CC2500();
                            }
                        }
                        Delay_uS(12);
                        CC2500_Transmit_Mode();
                        Delay_uS(20);
                        CC2500_Get_Status();
                    case (1):
                        break;
                    case (2):
                        break;
                    case (3):
                        break;
                }
		
		
		
		//while(!SPI_Buffer_Full_Bit);
                //Receiver_Data = SPI_Buffer_Reg;
                //Status_byte.bits = (unsigned char) Receiver_Data;
		//if((CC2500_Chip_State0 == 0) && (CC2500_Chip_State1 == 0) && (CC2500_Chip_State2 == 0))
		//{}  // In Idle Mode
		//else if ((CC2500_Chip_State0 == 0) && (CC2500_Chip_State1 == 0) && (CC2500_Chip_State2 == 1))
		//{}  // In receive Mode
		//else if ((CC2500_Chip_State0 == 0) && (CC2500_Chip_State1 == 1) && (CC2500_Chip_State2 == 1))
		//{
                NOP(); NOP();
               // Receiver_Data_Duplicate = Receiver_Data;
		//Receiver_Data_Duplicate &= 0x0F;
                //if (Receiver_Data_Duplicate >= 14)
                 //     CC2500_Clear_TX_FIFO();

		//}  // In Transmit Mode
			
		Delay_mS(250);	
		Delay_mS(250);
		Delay_mS(250);
                SSPEN = Disable;
                CC2500_module_CSn = 0;
	//#endif
	}
}
