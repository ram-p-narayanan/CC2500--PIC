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
#define PATABLE  	0x3E
#define TXFIFO   	0x3F
#define TXFIFO_Burst   	0x7F
#define RXFIFO   	0xBF
#define RXFIFO_Burst   	0xFF
//---------------------------------------------------------------
//CC2500 register data
//---------------------------------------------------------------
#define CC2500_IOCFG2_value				0x2F
#define CC2500_IOCFG1_value				0x2E
#define CC2500_IOCFG0D_value        	0x06
#define CC2500_FIFOTHR_value        	0x07
#define CC2500_SYNC1_value				0xD3
#define CC2500_SYNC0_value				0x91
#define CC2500_PKTLEN_value				0x03
#define CC2500_PKTCTRL1_value           0x84
#define CC2500_PKTCTRL0_value           0x04
#define CC2500_ADDR_value				0x00
#define CC2500_CHANNR_value				0x00
#define CC2500_FSCTRL1_value            0x09
#define CC2500_FSCTRL0_value            0x00
#define CC2500_FREQ2_value				0x5D
#define CC2500_FREQ1_value				0xD8
#define CC2500_FREQ0_value				0x9D
#define CC2500_MDMCFG4_value            0x2D
#define CC2500_MDMCFG3_value            0x3B
#define CC2500_MDMCFG2_value            0x73
#define CC2500_MDMCFG1_value            0x23
#define CC2500_MDMCFG0_value            0x3B
#define CC2500_DEVIATN_value            0x01
#define CC2500_MCSM2_value				0x07
#define CC2500_MCSM1_value              0x30
#define CC2500_MCSM0_value              0x18
#define CC2500_FOCCFG_value				0x1D
#define CC2500_BSCFG_value				0x1C
#define CC2500_AGCCTRL2_value           0xC7
#define CC2500_AGCCTRL1_value           0x00
#define CC2500_AGCCTRL0_value           0xB2
#define CC2500_WOREVT1_value            0x87
#define CC2500_WOREVT0_value            0x6B
#define CC2500_WORCTRL_value            0xF8
#define CC2500_FREND1_value				0xB6
#define CC2500_FREND0_value				0x10
#define CC2500_FSCAL3_value				0xEA
#define CC2500_FSCAL2_value				0x0A
#define CC2500_FSCAL1_value				0x00
#define CC2500_FSCAL0_value				0x11
#define CC2500_RCCTRL1_value            0x41
#define CC2500_RCCTRL0_value            0x00
#define CC2500_FSTEST_value				0x59
#define CC2500_PTEST_value				0x7F
#define CC2500_AGCTEST_value            0x3F
#define CC2500_TEST2_value				0x88
#define CC2500_TEST1_value				0x31
#define CC2500_TEST0_value				0x0B

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
//CC2500
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


