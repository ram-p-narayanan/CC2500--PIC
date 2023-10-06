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

/===============================================================
//Global variable Declarations
//===============================================================
unsigned char Loop_Variable;
unsigned char Temp1;
unsigned char Buffer_Data;
unsigned char Temp_data[DataBytes_Tx_Rx] = "TiinoResearchLabs\n\r";
unsigned char Receiver_Data[DataBytes_Tx_Rx];
unsigned char delay_Time_uS;
unsigned char delay_Time_mS;
//===============================================================
//Function Declarations start here
//===============================================================

void main(void)
{
while(1){
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
	
		CC2500_module_CSn = 0;
		Buffer_Data = SNOP;
		while(MISO == 1);
		SPI_Control_Reg = 0x20;
		Write_Byte_in_CC2500();
		Receiver_Data = Read_Byte_from_CC2500();
		SPI_Control_Reg = 0x00;
	
	/* See the content of the Receiver_Data variable and analyse it. */
	
		SizeOfTxData = sizeof(Temp_data);
		
		Write_Command_in_CC2500(TXFIFO);
		for (Loop_Count = 0; Loop_Count <= SizeOfTxData; Loop_Count++)
		{
			Buffer_Data = Temp_data[Loop_Count];
			Write_Byte_in_CC2500();
		}
		Delay_uS(12);
		CC2500_Transmit_Mode();	
		Delay_mS(250);	
		Delay_mS(250);
		Delay_mS(250);
	#endif
	}
}