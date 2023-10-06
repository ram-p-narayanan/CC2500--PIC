/* 
 * File:   reception.c
 * Author: jesus
 *
 * Created on October 13, 2014, 2:27 PM
 */
#include<pic.h>
#include "RF_UART_Main.h"
#include <xc.h>
#include "Reception.h"

unsigned char temp;
unsigned char Csn;
unsigned char receive_data;
unsigned char address;
unsigned char value;
unsigned char Rx;
unsigned char a;
unsigned char temp1;
unsigned char received_data[40];
unsigned char status_byte;
unsigned char duplicate_status_byte;
unsigned char current_state;
unsigned char available_bits;

void config_cc2500_reg(void)
{
	for(a=0;a<0x2F;a++)
	{
		temp1=CC2500_rfSettings[a];
		write_cc2500_reg(a,temp1);
	}
}
void init_GPIO()
{
    Chip_Select_TRIS = 0;
    clk_TRIS=0;
    SDI_TRIS=1;
    SDO_TRIS=0;

    Chip_Select_PORT = 1;
    SSPSTAT=0x40;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    PIE1bits.SSPIE=1;
    PIR1bits.SSPIF=0;
}
void write()
{
    SSPBUF=temp;
    while(SSPIF==0);
    SSPIF=0;
}

void write_cc2500_reg(unsigned char a,unsigned char temp1)
{
    Csn=0;
    temp=a;
    while(MISO==1);//check
    SSPCON=0x20;
    write();
    temp=temp1;
    write();
    Csn=1;
    SSPCON=0x00;
}


void send_command_cc2500(unsigned char command)
{
    Csn=0;
    temp= command;
    while(MISO==1);
    SSPCON=0x20;
    write();
    Csn=1;
}

unsigned char read_from_cc2500(unsigned char data)
 {
    SSPBUF=data;
    while(PIR1bits.SSPIF==0);
    SSPIF=0;
    while(BF==0);
    Rx = SSPBUF;
    return Rx;
 }
void FPower_on_reset_CC2500_CC1100(void)
{
	Csn=1;
	NOP();
	clk=0;
	NOP();
	MOSI=0;
	NOP();
	send_command_cc2500(SIDLE);
	Csn=1;
	Delay(2);
	Csn=0;
	Delay(2);
	Csn=1;
	Delay(15);
	Csn=0;
	temp=SRES;
	while(MISO==1);
	SSPCON=0x20;
	write();
	SSPCON=0x00;
	while(MISO==1);
	MOSI=0;
	Csn=1;
}
void Delay (unsigned char delay)

{
        unsigned int i,j,k;
        for(i=0;i<delay;i++)
        for(j=0;j<delay;j++);
}
void main()
{
    while(1)
    {
        UARTInit(9600);
        UARTWriteLine("***********************************************");
        init_GPIO();
        config_cc2500_reg();
        send_command_cc2500(SIDLE);
        send_command_cc2500(SRX);
        send_command_cc2500(SNOP);
        while(BF==0);
        status_byte=SSPBUF;
        duplicate_status_byte=status_byte;
        duplicate_status_byte&=0x70;
        current_state=duplicate_status_byte;
        switch(current_state)
        {
            case(0x00):
                    break;
            case(0x10):
                    duplicate_status_byte=status_byte;
                    duplicate_status_byte&=0x0F;
                    available_bits=duplicate_status_byte;
                    send_command_cc2500(RXFIFO);
                    for(unsigned char i=0;i<available_bits;i++)
                    {
                        received_data[i]=read_from_cc2500(SPI_data);
                        UARTWriteChar(received_data[i]);
                    }
                    break;
            case(0x20):
                    break;
            case(0x30):
                    break;
            case(0x40):
                    break;
            case(0x50):
                    break;
            case(0x60):
                    break;
            case(0x70):
                    break;
        }
        send_command_cc2500(SIDLE);
        send_command_cc2500(SCAL);
    }
}