//===============================================================
//PIC16F946
//===============================================================
#include <pic.h>
__CONFIG(0x30AC);
//---------------------------------------------------------------
//
//---------------------------------------------------------------
#define Enable	1
#define Disable	0

#define tx_function
//#define rx_function
//---------------------------------------------------------------
//
//---------------------------------------------------------------
unsigned char Bdelay_us;
unsigned char Bdelay_ms;
unsigned char Btemp1;
unsigned char Btemp2;
unsigned char Bloop_a;
unsigned char Bdata_buffer;
unsigned char Bp_r_data;
unsigned char Btx_data1;
unsigned char Btx_data2;
unsigned char Btx_data3;
unsigned char Brx_data1;
unsigned char Brx_data2;
unsigned char Brx_data3;
unsigned char BRSSI;
unsigned char BCRC;
unsigned char BLed_counter;
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
}Bflag1;
#define bCC2500_CC1100_recive_packet_ok	Bflag1.bits.bit0
#define bMCU_timeout_flag								Bflag1.bits.bit1
#define bCC2500_CC1100_interrupt_flag		Bflag1.bits.bit2
//---------------------------------------------------------------
//
//---------------------------------------------------------------
#include "MCU.h"
#include "Chipcon.h"
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void main(void)
{
#ifdef	tx_function
	FDelay_ms(50);
	FMCU_clear_all_ram();
	FMCU_Initial();
	FPower_on_reset_CC2500_CC1100();
	FCC2500_CC1100_Initial_all_registers();
	FCC2500_CC1100_Initial_PA_table();
	FCC2500_CC1100_clear_rx_fifo();
	FCC2500_CC1100_clear_tx_fifo();
	FCC2500_CC1100_frequency_calibration();
	FDelay_4us(200);
	FCC2500_CC1100_sleep_mode();
	FBuzzer_Enable();
	FDelay_ms(50);
	FBuzzer_Disable();
	BLed_counter=0;
	while(1)
	{
		CLRWDT();
		if(S1==0)
		{
			FBuzzer_Enable();
			FDelay_ms(50);
			FBuzzer_Disable();
			FTimer1_Disable();
			TMR1L=TIME_L_BYTE_4M;
			TMR1H=TIME_H_BYTE_4M;
			bMCU_timeout_flag=Disable;
			FTimer1_Enable();
			Btx_data1=0x58;
			Btx_data2=0x39;
			Btx_data3=BLed_counter;
			FRF_CC2500_CC1100_transmit_packet_data();
			INTF=0;
			bCC2500_CC1100_interrupt_flag=Disable;
			INTE=1;
			FCC2500_CC1100_receive_mode();
			while((bCC2500_CC1100_interrupt_flag==Disable)&&(bMCU_timeout_flag==Disable));
			bCC2500_CC1100_recive_packet_ok_flag=Disable;
			if(bCC2500_CC1100_interrupt_flag==Enable)
			{
				FRF_Interrupt_CC2500_CC1100_rx_data();
			}
			FCC2500_CC1100_idle_mode();
			FCC2500_CC1100_clear_rx_fifo();
			FCC2500_CC1100_sleep_mode();
			if(bCC2500_CC1100_recive_packet_ok_flag==Enable)
			{
				if(Brx_data1==0x58)
				{
					if(Brx_data2==0x39)
					{
						if(Brx_data3==BLed_counter)
						{
							FLED_7SEG_Output(BLed_counter);
						}
					}
				}
			}
			else
			{
				FLED_7SEG_Output(0x60);
			}
			while(S1==0)
			{
				CLRWDT();
			}
			FDelay_ms(50);
			BLed_counter++;
			if(BLed_counter>=0x0A)
			{
				BLed_counter=0;
			}
		}
	}
#endif
#ifdef	rx_function
	FDelay_ms(50);
	FMCU_clear_all_ram();
	FMCU_Initial();
	FPower_on_reset_CC2500_CC1100();
	FCC2500_CC1100_Initial_all_registers();
	FCC2500_CC1100_Initial_PA_table();
	FCC2500_CC1100_clear_rx_fifo();
	FCC2500_CC1100_clear_tx_fifo();
	FCC2500_CC1100_frequency_calibration();
	FDelay_4us(200);
	FBuzzer_Enable();
	FDelay_ms(50);
	FBuzzer_Disable();
	INTF=0;
	bCC2500_CC1100_interrupt_flag=Disable;
	INTE=1;
	FCC2500_CC1100_receive_mode();
	while(1)
	{
		CLRWDT();
		if(bCC2500_CC1100_interrupt_flag==Enable)
		{
			bCC2500_CC1100_recive_packet_ok_flag=Disable;
			FRF_Interrupt_CC2500_CC1100_rx_data();
			FCC2500_CC1100_clear_rx_fifo();
			if(bCC2500_CC1100_recive_packet_ok_flag==Enable)
			{
				if(Brx_data1==0x58)
				{
					if(Brx_data2==0x39)
					{
						FLED_7SEG_Output(Brx_data3);
						Btx_data1=0x58;
						Btx_data2=0x39;
						Btx_data3=Brx_data3;
						FRF_CC2500_CC1100_transmit_packet_data();
					}
				}
			}
			INTF=0;
			bCC2500_CC1100_interrupt_flag=Disable;
			INTE=1;
			FCC2500_CC1100_receive_mode();
		}
	}
#endif
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void interrupt isr(void)
{
	if(TMR1IF==1)
	{	
		TMR1L=TIME_L_BYTE_4M;
		TMR1H=TIME_H_BYTE_4M;
		TMR1IF=0;
		bMCU_timeout_flag=Enable;
	}
	if(INTF==1)
	{
		INTF=0;
		INTE=0;
		bCC2500_CC1100_interrupt_flag=Enable;
	}
}
