//---------------------------------------------------------------
//CC2500 register address
//---------------------------------------------------------------
#define IOCFG2			0x00
#define IOCFG1       	0x01
#define IOCFG0D      	0x02
#define FIFOTHR      	0x03
#define SYNC1        	0x04
#define SYNC0        	0x05
#define PKTLEN       	0x06
#define PKTCTRL1     	0x07
#define PKTCTRL0     	0x08
#define ADDR         	0x09
#define CHANNR       	0x0A
#define FSCTRL1      	0x0B
#define FSCTRL0      	0x0C
#define FREQ2        	0x0D
#define FREQ1        	0x0E
#define FREQ0        	0x0F
#define MDMCFG4      	0x10
#define MDMCFG3      	0x11
#define MDMCFG2      	0x12
#define MDMCFG1      	0x13
#define MDMCFG0      	0x14
#define DEVIATN      	0x15
#define MCSM2        	0x16
#define MCSM1        	0x17
#define MCSM0        	0x18
#define FOCCFG       	0x19
#define BSCFG        	0x1A
#define AGCCTRL2     	0x1B
#define AGCCTRL1     	0x1C
#define AGCCTRL0     	0x1D
#define WOREVT1      	0x1E
#define WOREVT0      	0x1F
#define WORCTRL      	0x20
#define FREND1       	0x21
#define FREND0       	0x22
#define FSCAL3       	0x23
#define FSCAL2       	0x24
#define FSCAL1       	0x25
#define FSCAL0       	0x26
#define RCCTRL1      	0x27
#define RCCTRL0      	0x28
#define FSTEST       	0x29
#define PTEST        	0x2A
#define AGCTEST      	0x2B
#define TEST2        	0x2C
#define TEST1        	0x2D
#define TEST0        	0x2E
#define PARTNUM      	0x30
#define VERSION      	0x31
#define FREQEST      	0x32
#define LQI          	0x33
#define RSSI         	0x34
#define MARCSTATE    	0x35
#define WORTIME1     	0x36
#define WORTIME0     	0x37
#define PKTSTATUS    	0x38
#define VCO_VC_DAC   	0x39
#define TXBYTES      	0x3A
#define RXBYTES      	0x3B
#define PATABLE  		0x3E
#define TXFIFO   		0x3F
#define RXFIFO   		0x3F
//---------------------------------------------------------------
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
//---------------------------------------------------------------
//CC1100 register data
//---------------------------------------------------------------
#define CC1100_IOCFG2_value  	0x00
#define CC1100_IOCFG1_value		0x00
#define CC1100_IOCFG0D_value	0x00
#define CC1100_FIFOTHR_value	0x00
#define CC1100_SYNC1_value		0x00
#define CC1100_SYNC0_value		0x00
#define CC1100_PKTLEN_value		0x00
#define CC1100_PKTCTRL1_value	0x00
#define CC1100_PKTCTRL0_value	0x00
#define CC1100_ADDR_value			0x00
#define CC1100_CHANNR_value		0x00
#define CC1100_FSCTRL1_value	0x00
#define CC1100_FSCTRL0_value	0x00
#define CC1100_FREQ2_value		0x00
#define CC1100_FREQ1_value		0x00
#define CC1100_FREQ0_value		0x00
#define CC1100_MDMCFG4_value	0x00
#define CC1100_MDMCFG3_value	0x00
#define CC1100_MDMCFG2_value	0x00
#define CC1100_MDMCFG1_value	0x00
#define CC1100_MDMCFG0_value	0x00
#define CC1100_DEVIATN_value	0x00
#define CC1100_MCSM2_value		0x00
#define CC1100_MCSM1_value		0x00
#define CC1100_MCSM0_value		0x00
#define CC1100_FOCCFG_value		0x00
#define CC1100_BSCFG_value		0x00
#define CC1100_AGCCTRL2_value	0x00
#define CC1100_AGCCTRL1_value	0x00
#define CC1100_AGCCTRL0_value	0x00
#define CC1100_WOREVT1_value	0x00
#define CC1100_WOREVT0_value	0x00
#define CC1100_WORCTRL_value	0x00
#define CC1100_FREND1_value		0x00
#define CC1100_FREND0_value		0x00
#define CC1100_FSCAL3_value		0x00
#define CC1100_FSCAL2_value		0x00
#define CC1100_FSCAL1_value		0x00
#define CC1100_FSCAL0_value		0x00
#define CC1100_RCCTRL1_value	0x00
#define CC1100_RCCTRL0_value	0x00
#define CC1100_FSTEST_value		0x00
#define CC1100_PTEST_value		0x00
#define CC1100_AGCTEST_value	0x00
#define CC1100_TEST2_value		0x00
#define CC1100_TEST1_value		0x00
#define CC1100_TEST0_value		0x00
//---------------------------------------------------------------
//command
//---------------------------------------------------------------
#define SRES     			0x30
#define SFSTXON  			0x31
#define SXOFF    			0x32
#define SCAL     			0x33
#define SRX      			0x34
#define STX      			0x35
#define SIDLE    			0x36
#define SAFC     			0x37
#define SWOR     			0x38
#define SPWD     			0x39
#define SFRX     			0x3A
#define SFTX     			0x3B
#define SWORRST  			0x3C
#define SNOP     			0x3D
//---------------------------------------------------------------
//CC2500 暫存器資料表
//---------------------------------------------------------------
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
//---------------------------------------------------------------
//0dBm
//---------------------------------------------------------------
const unsigned char CC2500_patable_value[8]=
{
	0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FWrite_one_byte_to_RF(void)
{
	SSPBUF=Bdata_buffer;
	while(SSPIF==0);
	SSPIF=0;
	while(BF==0);
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FRead_one_byte_from_RF(void)
{
	SSPBUF=0x00;
	while(SSPIF==0);
	SSPIF=0;
	while(BF==0);
	Bp_r_data=SSPBUF;
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FWrite_register_to_CC2500_CC1100(unsigned char Bp_w_address,unsigned char Bp_w_data)
{
	CC2500_module_CSN=0;
	Bdata_buffer=Bp_w_address;
	while(MISO==1);
	SSPCON=0x20;
	FWrite_one_byte_to_RF();
	Bdata_buffer=Bp_w_data;
	FWrite_one_byte_to_RF();
	CC2500_module_CSN=1;
	SSPCON=0x00;
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FWrite_command_to_CC2500_CC1100(unsigned char Bp_w_command)
{
	CC2500_module_CSN=0;
	Bdata_buffer=Bp_w_command;
	while(MISO==1);
	SSPCON=0x20;
	FWrite_one_byte_to_RF();
	CC2500_module_CSN=1;
	SSPCON=0x00;
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FRead_status_register_from_CC2500_CC1100(unsigned char Bp_w_address)
{
	CC2500_module_CSN=0;
	Bdata_buffer=Bp_w_address+0xC0;
	while(MISO==1);
	SSPCON=0x20;
	FWrite_one_byte_to_RF();
	FRead_one_byte_from_RF();
	CC2500_module_CSN=1;
	SSPCON=0x00;
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FRead_register_from_CC2500_CC1100(unsigned char Bp_w_address)
{
	CC2500_module_CSN=0;
	Bdata_buffer=Bp_w_address+0x80;
	while(MISO==1);
	SSPCON=0x20;
	FWrite_one_byte_to_RF();
	FRead_one_byte_from_RF();
	CC2500_module_CSN=1;
	SSPCON=0x00;
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FPower_on_reset_CC2500_CC1100(void)
{
	CC2500_module_CSN=1;
	NOP();
	SCLK=0;
	NOP();
	MOSI=0;
	NOP();
	FWrite_command_to_CC2500_CC1100(SIDLE);
	CC2500_module_CSN=1;
	FDelay_4us(2);
	CC2500_module_CSN=0;
	FDelay_4us(2);
	CC2500_module_CSN=1;
	FDelay_4us(15);
	CC2500_module_CSN=0;
	Bdata_buffer=SRES;
	while(MISO==1);
	SSPCON=0x20;
	FWrite_one_byte_to_RF();
	SSPCON=0x00;
	while(MISO==1);
	MOSI=0;
	CC2500_module_CSN=1;
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FCC2500_CC1100_Initial_all_registers(void)
{
	for(Bloop_a=0;Bloop_a<0x2F;Bloop_a++)
	{
		Btemp1=CC2500_rfSettings[Bloop_a];
		FWrite_register_to_CC2500_CC1100(Bloop_a,Btemp1);
	}
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FCC2500_CC1100_Initial_PA_table(void)
{
	CC2500_module_CSN=0;
	Bdata_buffer=PATABLE+0x40;
	while(MISO==1);
	SSPCON=0x20;
	FWrite_one_byte_to_RF();
	for(Bloop_a=0;Bloop_a<8;Bloop_a++)
	{
		Bdata_buffer=CC2500_patable_value[Bloop_a];
		FWrite_one_byte_to_RF();
	}
	CC2500_module_CSN=1;
	SSPCON=0x00;
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
#define FCC2500_CC1100_idle_mode()							FWrite_command_to_CC2500_CC1100(SIDLE)
#define FCC2500_CC1100_clear_rx_fifo()					FWrite_command_to_CC2500_CC1100(SFRX)
#define FCC2500_CC1100_clear_tx_fifo()					FWrite_command_to_CC2500_CC1100(SFTX)
#define FCC2500_CC1100_frequency_calibration()	FWrite_command_to_CC2500_CC1100(SCAL)
#define FCC2500_CC1100_sleep_mode()							FWrite_command_to_CC2500_CC1100(SPWD)
#define FCC2500_CC1100_receive_mode()						FWrite_command_to_CC2500_CC1100(SRX)
#define FCC2500_CC1100_transmit_mode()					FWrite_command_to_CC2500_CC1100(STX)
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FRF_CC2500_CC1100_transmit_packet_data(void)
{
	CC2500_module_CSN=0;
	Bdata_buffer=TXFIFO+0x40; //設定暫存器為TXFIFO並且為連續寫入
	while(MISO==1);
	SSPCON=0x20;
	FWrite_one_byte_to_RF();
	Bdata_buffer=Btx_data1;
	FWrite_one_byte_to_RF();
	Bdata_buffer=Btx_data2;
	FWrite_one_byte_to_RF();
	Bdata_buffer=Btx_data3;
	FWrite_one_byte_to_RF();
	CC2500_module_CSN=1;
	SSPCON=0x00;
	FWrite_command_to_CC2500_CC1100(STX);
	while(GDO0_DIO==0);
	while(GDO0_DIO==1);
}
//---------------------------------------------------------------
//
//---------------------------------------------------------------
void FRF_Interrupt_CC2500_CC1100_rx_data(void)
{
	Brx_data1=0x00;
	Brx_data2=0x00;
	Brx_data3=0x00;
	while(GDO0_DIO==1);//等待接收完成
	FRead_status_register_from_CC2500_CC1100(RXBYTES);//讀取RXBYTES確認RXFIFO有多少資料
	if(Bp_r_data==CC2500_PKTLEN_value+2)//RXFIFO內資料長度為固定資料長度+2
	{
		CC2500_module_CSN=0;
		Bdata_buffer=RXFIFO+0xC0;//設定CC2500暫存器為RXFIFO並且為連續讀出
		while(MISO==1);
		SSPCON=0x20;
		FWrite_one_byte_to_RF();
		FRead_one_byte_from_RF();
		Brx_data1=Bp_r_data;
		FRead_one_byte_from_RF();
		Brx_data2=Bp_r_data;
		FRead_one_byte_from_RF();
		Brx_data3=Bp_r_data;
		FRead_one_byte_from_RF();//讀出為RSSI資料
		BRSSI=Bp_r_data;
		FRead_one_byte_from_RF();//讀出為CRC資料
		BCRC=Bp_r_data;
		CC2500_module_CSN=1;
		SSPCON=0x00;
		if(BCRC&0x80)//判斷CRC是否正確
		{
			bCC2500_CC1100_recive_packet_ok_flag=Enable;
		}
	}
}

