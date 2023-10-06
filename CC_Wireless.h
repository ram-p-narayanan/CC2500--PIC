#fuses HS,NOWDT,NOPROTECT
#use delay(clock=20000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

// Configuration Registers
#define TI_CCxxx0_IOCFG2       0x00     // GDO2 output pin configuration
#define TI_CCxxx0_IOCFG1       0x01     // GDO1 output pin configuration
#define TI_CCxxx0_IOCFG0       0x02     // GDO0 output pin configuration
#define TI_CCxxx0_FIFOTHR      0x03     // RX FIFO and TX FIFO thresholds
#define TI_CCxxx0_SYNC1        0x04     // Sync word, high byte
#define TI_CCxxx0_SYNC0        0x05     // Sync word, low byte
#define TI_CCxxx0_PKTLEN       0x06     // Packet length
#define TI_CCxxx0_PKTCTRL1     0x07     // Packet automation control
#define TI_CCxxx0_PKTCTRL0     0x08     // Packet automation control
#define TI_CCxxx0_ADDR         0x09     // Device address
#define TI_CCxxx0_CHANNR       0x0A     // Channel number
#define TI_CCxxx0_FSCTRL1      0x0B     // Frequency synthesizer control
#define TI_CCxxx0_FSCTRL0      0x0C     // Frequency synthesizer control
#define TI_CCxxx0_FREQ2        0x0D     // Frequency control word, high byte
#define TI_CCxxx0_FREQ1        0x0E     // Frequency control word, middle byte
#define TI_CCxxx0_FREQ0        0x0F     // Frequency control word, low byte
#define TI_CCxxx0_MDMCFG4      0x10     // Modem configuration
#define TI_CCxxx0_MDMCFG3      0x11     // Modem configuration
#define TI_CCxxx0_MDMCFG2      0x12     // Modem configuration
#define TI_CCxxx0_MDMCFG1      0x13     // Modem configuration
#define TI_CCxxx0_MDMCFG0      0x14     // Modem configuration
#define TI_CCxxx0_DEVIATN      0x15     // Modem deviation setting
#define TI_CCxxx0_MCSM2        0x16     // Main Radio Cntrl State Machine config
#define TI_CCxxx0_MCSM1        0x17     // Main Radio Cntrl State Machine config
#define TI_CCxxx0_MCSM0        0x18     // Main Radio Cntrl State Machine config
#define TI_CCxxx0_FOCCFG       0x19     // Frequency Offset Compensation config
#define TI_CCxxx0_BSCFG        0x1A     // Bit Synchronization configuration
#define TI_CCxxx0_AGCCTRL2     0x1B     // AGC control
#define TI_CCxxx0_AGCCTRL1     0x1C     // AGC control
#define TI_CCxxx0_AGCCTRL0     0x1D     // AGC control
#define TI_CCxxx0_WOREVT1      0x1E     // High byte Event 0 timeout
#define TI_CCxxx0_WOREVT0      0x1F     // Low byte Event 0 timeout
#define TI_CCxxx0_WORCTRL      0x20     // Wake On Radio control
#define TI_CCxxx0_FREND1       0x21     // Front end RX configuration
#define TI_CCxxx0_FREND0       0x22     // Front end TX configuration
#define TI_CCxxx0_FSCAL3       0x23     // Frequency synthesizer calibration
#define TI_CCxxx0_FSCAL2       0x24     // Frequency synthesizer calibration
#define TI_CCxxx0_FSCAL1       0x25     // Frequency synthesizer calibration
#define TI_CCxxx0_FSCAL0       0x26     // Frequency synthesizer calibration
#define TI_CCxxx0_RCCTRL1      0x27     // RC oscillator configuration
#define TI_CCxxx0_RCCTRL0      0x28     // RC oscillator configuration
#define TI_CCxxx0_FSTEST       0x29     // Frequency synthesizer cal control
#define TI_CCxxx0_PTEST        0x2A     // Production test
#define TI_CCxxx0_AGCTEST      0x2B     // AGC test
#define TI_CCxxx0_TEST2        0x2C     // Various test settings
#define TI_CCxxx0_TEST1        0x2D     // Various test settings
#define TI_CCxxx0_TEST0        0x2E     // Various test settings
#define TI_CCxxx0_PATABLE      0x3E

#define SPI_MODE_0  (SPI_L_TO_H | SPI_XMIT_L_TO_H)
#define SPI_MODE_1  (SPI_L_TO_H)
#define SPI_MODE_2  (SPI_H_TO_L)
#define SPI_MODE_3  (SPI_H_TO_L | SPI_XMIT_L_TO_H)
#define SPI_SS   PIN_C2

#define VERSION_NUMBER          0xF0
#define PART_NUMBER             0xF1
#define NUMBER_TXBYTES_IN_FIFO  0xFA
#define NUMBER_RXBYTES_IN_FIFO  0xFB

#define DUMMY           0x00
#define SCAL            0x33
#define SRX             0x34
#define STX             0x35
#define SIDLE           0x36
#define SFRX            0x3A
#define SFTX            0x3B
#define SNOP            0x3D
#define TX_FIFO         0x3F


#define  STRING_SIZE    51          // The number of characters allowed to input


void delay(unsigned int delay_us);
void CC_Initial_Check();
void CC_SetIdleMode();
void CC_SetReceiveModeMode();
void CC_SetTransmitModeMode();
void CC_ClearTransmitFIFO();
void CC_TransmitData();
void CC_TransmitData1();
void CC_TransmitNumber();
void CC_CheckNoOfBytesinTXFIFO();
void CC_WriteRFSettings();
void TI_CC_SPIWriteReg(char addr, char value);


static unsigned char ReceiveValue;
static unsigned char TransmitData[10];

// Append a bit After every Data which is sent and De-append it on the
// receiving Side

/* This Function Checks the initial working of SPI COmmunication with CC2500.
 * This is done by checking whether the CC module returns the correct version
 * and part number to the controller*/

   void CC_Initial_Check()
{
    output_low(SPI_SS);
    delay_us(1);
    spi_write(VERSION_NUMBER);
    ReceiveValue = spi_read(DUMMY);
    if(ReceiveValue == 0x80)
        printf("Version Number Correct \r");
    delay_us(1);
    spi_write(PART_NUMBER);
    ReceiveValue = spi_read(DUMMY);
    if(ReceiveValue == 0x03)
        printf("Part Number Correct \r");
    delay_us(1);
    output_high(SPI_SS);
}

/* There are 47 Configuration Registers in CC2500. Some of the register's
 * default values may be the optimum ones, but, it is required to set the
 * values of most of the registers. This is performed by using the
 * SmartRF Studio.*/

void CC_WriteRFSettings(void)
{
	// Write register settings
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG2,   0x29);// GDO2 output pin config.
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG1,   0x2E);// GDO1 output pin config.
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG0,   0x01);// GDO0 output pin config.
    TI_CC_SPIWriteReg(TI_CCxxx0_FIFOTHR,  0x07);
    TI_CC_SPIWriteReg(TI_CCxxx0_SYNC1,    0xD3);
    TI_CC_SPIWriteReg(TI_CCxxx0_SYNC0,    0x91);
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTLEN,   0xFF);// Packet length.
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTCTRL1, 0x04);// Packet automation control.
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTCTRL0, 0x01);// Packet automation control.
    TI_CC_SPIWriteReg(TI_CCxxx0_ADDR,     0x00);// Device address.
   // TI_CC_SPIWriteReg(TI_CCxxx0_CHANNR,   0x03);// Channel number.

    TI_CC_SPIWriteReg(TI_CCxxx0_CHANNR,   0x00);// Channel number.

    ///********************************************************8



    TI_CC_SPIWriteReg(TI_CCxxx0_FSCTRL1,  0x08);// Freq synthesizer control.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCTRL0,  0x00);// Freq synthesizer control.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ2,    0x5D);// Freq control word, high byte
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ1,    0x44);// Freq control word, mid byte.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ0,    0xEC);// Freq control word, low byte.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG4,  0x86);// Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG3,  0x83);// Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG2,  0x03);// Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG1,  0x43);// Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG0,  0x38);// Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_DEVIATN,  0x44);// Modem dev (when FSK mod en)
    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM2 ,   0x07);// MainRadio Cntrl State Machine
    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM1 ,   0x3E);// MainRadio Cntrl State Machine
    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM0 ,   0x18);// MainRadio Cntrl State Machine
    TI_CC_SPIWriteReg(TI_CCxxx0_FOCCFG,   0x16);// Freq Offset Compens. Config
    TI_CC_SPIWriteReg(TI_CCxxx0_BSCFG,    0x6C);//  Bit synchronization config.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL2, 0x03);// AGC control.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL1, 0x40);// AGC control.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL0, 0x91);// AGC control.
    TI_CC_SPIWriteReg(TI_CCxxx0_WOREVT1,  0x87);
    TI_CC_SPIWriteReg(TI_CCxxx0_WOREVT0,  0x6B);
    TI_CC_SPIWriteReg(TI_CCxxx0_WORCTRL,  0xF8);
    TI_CC_SPIWriteReg(TI_CCxxx0_FREND1,   0x56);// Front end RX configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREND0,   0x10);// Front end RX configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL3,   0xA9);// Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL2,   0x0A);// Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL1,   0x00);// Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL0,   0x11);// Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_RCCTRL1,  0x41);
    TI_CC_SPIWriteReg(TI_CCxxx0_RCCTRL0,  0x00);
    TI_CC_SPIWriteReg(TI_CCxxx0_FSTEST,   0x59);// Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_PTEST,    0x7F);
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCTEST,  0x3F);
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST2,    0x81);// Various test settings.
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST1,    0x35);// Various test settings.
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST0,    0x0B);// Various test settings.
    TI_CC_SPIWriteReg(TI_CCxxx0_PATABLE , 0xFE);
}


void TI_CC_SPIWriteReg(char addr, char value)
{
    output_low(SPI_SS);
    delay_us(1);
    spi_write(addr);
    delay_us(1);
    spi_write(value);
    delay_us(1);
    output_high(SPI_SS);
}

void CC_SetIdleMode()
{
    output_low(SPI_SS);
    delay_us(1);
    spi_write(SIDLE);
    ReceiveValue = spi_read(SNOP);
    delay_us(1);
    spi_write(SFTX);
    ReceiveValue = spi_read(SNOP);
    delay_us(1);
    spi_write(SFRX);
    ReceiveValue = spi_read(SNOP);
    output_high(SPI_SS);
}

void CC_ClearTransmitFIFO()
{
    output_low(SPI_SS);
    delay_us(1);
    spi_write(SFTX);
    ReceiveValue = spi_read(SNOP);
    delay_us(1);
    output_high(SPI_SS);
}

void CC_TransmitData()
{
    static unsigned char CountVar;
    while(TransmitData[CountVar] != '\0')
    {
        TI_CC_SPIWriteReg(TX_FIFO , TransmitData[CountVar]);
        ++CountVar;
    }
    CountVar = 0;
}

void CC_CheckNoOfBytesinTXFIFO()
{
    output_low(SPI_SS);
    delay_us(1);
    spi_write(NUMBER_TXBYTES_IN_FIFO);
    ReceiveValue = spi_read(DUMMY);
    delay_us(1);
    output_high(SPI_SS);
}

void CC_CheckNoOfBytesinRXFIFO()
{
    output_low(SPI_SS);
    delay_us(1);
    spi_write(NUMBER_RXBYTES_IN_FIFO);
    ReceiveValue = spi_read(DUMMY);
    delay_us(1);
    output_high(SPI_SS);
}

void CC_SetReceiveModeMode()
{
    output_low(SPI_SS);
    delay_us(1);
    spi_write(SFRX);
    ReceiveValue = spi_read(SNOP);
    spi_write(SRX);
    ReceiveValue = spi_read(SNOP);
    delay_us(1);
    output_high(SPI_SS);

}

void CC_SetTransmitModeMode()
{
    output_low(SPI_SS);
    delay_us(1);
    spi_write(SIDLE);
    ReceiveValue = spi_read(SNOP);
    delay_us(10);
    spi_write(SFTX);
    ReceiveValue = spi_read(SNOP);
    delay_us(1);
    spi_write(STX);
    ReceiveValue = spi_read(SNOP);
    delay_us(1);
    CC_CheckNoOfBytesinTXFIFO();
    CC_TransmitData();
    delay_us(250);

    CC_CheckNoOfBytesinTXFIFO();
    delay_us(1);
    spi_write(STX);
    ReceiveValue = spi_read(SNOP);

    delay_us(250);
    spi_write(SFTX);
    ReceiveValue = spi_read(SNOP);
    delay_us(1);
    output_high(SPI_SS);
}

