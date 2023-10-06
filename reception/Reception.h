/* 
 * File:   Reception.h
 * Author: jesus
 *
 * Created on October 14, 2014, 3:57 PM
 */

#ifndef RECEPTION_H
#define	RECEPTION_H


#define clk     RC3
#define MISO    RC4
#define MOSI    RC5

#define clk_TRIS TRISCbits.TRISC3
#define SDI_TRIS TRISCbits.TRISC4
#define SDO_TRIS TRISCbits.TRISC5
#define Chip_Select_TRIS  TRISCbits.TRISC2
#define Chip_Select_PORT  PORTCbits.RC2
#define SRX     0x34
#define SIDLE   0x36
#define SCAL    0x33
#define SRES    0x30
#define RXFIFO  0xFF
#define SPI_data    0x00
#define SNOP    0x3D


//CC2500 register data
//---------------------------------------------------------------
#define CC2500_IOCFG2_value		0x2F
#define CC2500_IOCFG1_value		0x2E
#define CC2500_IOCFG0D_value	0x06
#define CC2500_FIFOTHR_value	0x07
#define CC2500_SYNC1_value		0xD3
#define CC2500_SYNC0_value		0x91
#define CC2500_PKTLEN_value		0x03
#define CC2500_PKTCTRL1_value	0x84
#define CC2500_PKTCTRL0_value	0x04
#define CC2500_ADDR_value			0x00
#define CC2500_CHANNR_value		0x00
#define CC2500_FSCTRL1_value	0x09
#define CC2500_FSCTRL0_value	0x00
#define CC2500_FREQ2_value		0x5D
#define CC2500_FREQ1_value		0xD8
#define CC2500_FREQ0_value		0x9D
#define CC2500_MDMCFG4_value	0x2D
#define CC2500_MDMCFG3_value	0x3B
#define CC2500_MDMCFG2_value	0x73
#define CC2500_MDMCFG1_value	0x23
#define CC2500_MDMCFG0_value	0x3B
#define CC2500_DEVIATN_value	0x01
#define CC2500_MCSM2_value		0x07
#define CC2500_MCSM1_value  	0x30
#define CC2500_MCSM0_value  	0x18
#define CC2500_FOCCFG_value		0x1D
#define CC2500_BSCFG_value		0x1C
#define CC2500_AGCCTRL2_value	0xC7
#define CC2500_AGCCTRL1_value	0x00
#define CC2500_AGCCTRL0_value	0xB2
#define CC2500_WOREVT1_value	0x87
#define CC2500_WOREVT0_value	0x6B
#define CC2500_WORCTRL_value	0xF8
#define CC2500_FREND1_value		0xB6
#define CC2500_FREND0_value		0x10
#define CC2500_FSCAL3_value		0xEA
#define CC2500_FSCAL2_value		0x0A
#define CC2500_FSCAL1_value		0x00
#define CC2500_FSCAL0_value		0x11
#define CC2500_RCCTRL1_value	0x41
#define CC2500_RCCTRL0_value	0x00
#define CC2500_FSTEST_value		0x59
#define CC2500_PTEST_value		0x7F
#define CC2500_AGCTEST_value	0x3F
#define CC2500_TEST2_value		0x88
#define CC2500_TEST1_value		0x31
#define CC2500_TEST0_value		0x0B

void init_GPIO();
void send_command_cc2500(unsigned char command);
unsigned char read_from_cc2500(unsigned char );
void write();
void read();
void Delay (unsigned char delay);
void write_cc2500_reg(unsigned char ,unsigned char );
void config_cc2500_reg(void);
void UARTInit();

const unsigned char CC2500_rfSettings[0x2F]=
{
	CC2500_IOCFG2_value,
	CC2500_IOCFG1_value,
	CC2500_IOCFG0D_value,
	CC2500_FIFOTHR_value,
	CC2500_SYNC1_value,
	CC2500_SYNC0_value,
	CC2500_PKTLEN_value,
	CC2500_PKTCTRL1_value,
	CC2500_PKTCTRL0_value,
	CC2500_ADDR_value,
	CC2500_CHANNR_value,
	CC2500_FSCTRL1_value,
	CC2500_FSCTRL0_value,
	CC2500_FREQ2_value,
	CC2500_FREQ1_value,
	CC2500_FREQ0_value,
	CC2500_MDMCFG4_value,
	CC2500_MDMCFG3_value,
	CC2500_MDMCFG2_value,
	CC2500_MDMCFG1_value,
	CC2500_MDMCFG0_value,
	CC2500_DEVIATN_value,
	CC2500_MCSM2_value,
	CC2500_MCSM1_value,
	CC2500_MCSM0_value,
	CC2500_FOCCFG_value,
	CC2500_BSCFG_value,
	CC2500_AGCCTRL2_value,
	CC2500_AGCCTRL1_value,
	CC2500_AGCCTRL0_value,
	CC2500_WOREVT1_value,
	CC2500_WOREVT0_value,
	CC2500_WORCTRL_value,
	CC2500_FREND1_value,
	CC2500_FREND0_value,
	CC2500_FSCAL3_value,
	CC2500_FSCAL2_value,
	CC2500_FSCAL1_value,
	CC2500_FSCAL0_value,
	CC2500_RCCTRL1_value,
	CC2500_RCCTRL0_value,
	CC2500_FSTEST_value,
	CC2500_PTEST_value,
	CC2500_AGCTEST_value,
	CC2500_TEST2_value,
	CC2500_TEST1_value,
	CC2500_TEST0_value
};

#endif	/* RECEPTION_H */

