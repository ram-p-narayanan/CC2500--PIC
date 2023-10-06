// Configuration Registers
#define TI_CCxxx0_IOCFG2       0x00        // GDO2 output pin configuration
#define TI_CCxxx0_IOCFG1       0x01        // GDO1 output pin configuration
#define TI_CCxxx0_IOCFG0       0x02        // GDO0 output pin configuration
#define TI_CCxxx0_FIFOTHR      0x03        // RX FIFO and TX FIFO thresholds
#define TI_CCxxx0_SYNC1        0x04        // Sync word, high byte
#define TI_CCxxx0_SYNC0        0x05        // Sync word, low byte
#define TI_CCxxx0_PKTLEN       0x06        // Packet length
#define TI_CCxxx0_PKTCTRL1     0x07        // Packet automation control
#define TI_CCxxx0_PKTCTRL0     0x08        // Packet automation control
#define TI_CCxxx0_ADDR         0x09        // Device address
#define TI_CCxxx0_CHANNR       0x0A        // Channel number
#define TI_CCxxx0_FSCTRL1      0x0B        // Frequency synthesizer control
#define TI_CCxxx0_FSCTRL0      0x0C        // Frequency synthesizer control
#define TI_CCxxx0_FREQ2        0x0D        // Frequency control word, high byte
#define TI_CCxxx0_FREQ1        0x0E        // Frequency control word, middle byte
#define TI_CCxxx0_FREQ0        0x0F        // Frequency control word, low byte
#define TI_CCxxx0_MDMCFG4      0x10        // Modem configuration
#define TI_CCxxx0_MDMCFG3      0x11        // Modem configuration
#define TI_CCxxx0_MDMCFG2      0x12        // Modem configuration
#define TI_CCxxx0_MDMCFG1      0x13        // Modem configuration
#define TI_CCxxx0_MDMCFG0      0x14        // Modem configuration
#define TI_CCxxx0_DEVIATN      0x15        // Modem deviation setting
#define TI_CCxxx0_MCSM2        0x16        // Main Radio Cntrl State Machine config
#define TI_CCxxx0_MCSM1        0x17        // Main Radio Cntrl State Machine config
#define TI_CCxxx0_MCSM0        0x18        // Main Radio Cntrl State Machine config
#define TI_CCxxx0_FOCCFG       0x19        // Frequency Offset Compensation config
#define TI_CCxxx0_BSCFG        0x1A        // Bit Synchronization configuration
#define TI_CCxxx0_AGCCTRL2     0x1B        // AGC control
#define TI_CCxxx0_AGCCTRL1     0x1C        // AGC control
#define TI_CCxxx0_AGCCTRL0     0x1D        // AGC control
#define TI_CCxxx0_WOREVT1      0x1E        // High byte Event 0 timeout
#define TI_CCxxx0_WOREVT0      0x1F        // Low byte Event 0 timeout
#define TI_CCxxx0_WORCTRL      0x20        // Wake On Radio control
#define TI_CCxxx0_FREND1       0x21        // Front end RX configuration
#define TI_CCxxx0_FREND0       0x22        // Front end TX configuration
#define TI_CCxxx0_FSCAL3       0x23        // Frequency synthesizer calibration
#define TI_CCxxx0_FSCAL2       0x24        // Frequency synthesizer calibration
#define TI_CCxxx0_FSCAL1       0x25        // Frequency synthesizer calibration
#define TI_CCxxx0_FSCAL0       0x26        // Frequency synthesizer calibration
#define TI_CCxxx0_RCCTRL1      0x27        // RC oscillator configuration
#define TI_CCxxx0_RCCTRL0      0x28        // RC oscillator configuration
#define TI_CCxxx0_FSTEST       0x29        // Frequency synthesizer cal control
#define TI_CCxxx0_PTEST        0x2A        // Production test
#define TI_CCxxx0_AGCTEST      0x2B        // AGC test
#define TI_CCxxx0_TEST2        0x2C        // Various test settings
#define TI_CCxxx0_TEST1        0x2D        // Various test settings
#define TI_CCxxx0_TEST0        0x2E        // Various test settings
#define TI_CCxxx0_PATABLE      0x3E

#define SPI_MODE_0  (SPI_L_TO_H | SPI_XMIT_L_TO_H)
#define SPI_MODE_1  (SPI_L_TO_H)
#define SPI_MODE_2  (SPI_H_TO_L)
#define SPI_MODE_3  (SPI_H_TO_L | SPI_XMIT_L_TO_H)
#define SPI_SS   PIN_C2

#define VERSION_NUMBER          0xF0
#define PART_NUMBER             0xF1
#define RSSI                    0xF4
#define LQI                     0xF3
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
#define RX_FIFO         0xBF


#define RSSI_OFFSET2p4         71
#define RSSI_OFFSET10          69
#define RSSI_OFFSET250         72
#define RSSI_OFFSET500         72

void CC_Initial_Check();
void CC_SetIdleMode();
void CC_SetReceiveModeMode();
void CC_SetTransmitModeMode();
void CC_ClearTransmitFIFO();
void CC_TransmitData();
void CC_CheckNoOfBytesinTXFIFO();
void CC_CheckNoOfBytesinRXFIFO();
void CC_WriteRFSettings();
void TI_CC_SPIWriteReg(char addr, char value);
void GetUserInput();
void GetRSSI();

static unsigned char Temp;
static unsigned char ReceiveValue;
static unsigned char ReceiveData[10],ReceiveData1[10];
static unsigned char TransmitData[20] = "TIINO";
//static unsigned int dummyCount;
int RxSignalStrength;
static unsigned char UserInput_Mode;
static unsigned int UserInput_DataRate;
static unsigned char ReceiverOptimization;
static unsigned char atoiData[1];
int Integer;
static char RSSIConstant;
int LinkQIndicator;

void CC_Initial_Check()
{
    output_low(SPI_SS);																	delay_ms(1);
    spi_write(VERSION_NUMBER);
    ReceiveValue = spi_read(DUMMY);
    printf("The VERSION NUMBER is 0x%X",ReceiveValue);									delay_ms(2);
    spi_write(PART_NUMBER);
    ReceiveValue = spi_read(DUMMY);
    printf("The PART NUMBER is 0x%X",ReceiveValue);										delay_ms(2);
    output_high(SPI_SS);
}

void CC_WriteRFSettings(void)
{
	// Write register settings
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG2,   0x29);  // GDO2 output pin config.
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG1,   0x2E);  // GDO1 output pin config.
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG0,   0x01);  // GDO0 output pin config.
    TI_CC_SPIWriteReg(TI_CCxxx0_FIFOTHR,  0x07);
    TI_CC_SPIWriteReg(TI_CCxxx0_SYNC1,    0xD3);
    TI_CC_SPIWriteReg(TI_CCxxx0_SYNC0,    0x91);
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTLEN,   0xFF);  // Packet length.
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTCTRL1, 0x04);  // Packet automation control.
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTCTRL0, 0x01);  // Packet automation control.
    TI_CC_SPIWriteReg(TI_CCxxx0_ADDR,     0x00);  // Device address.
    TI_CC_SPIWriteReg(TI_CCxxx0_CHANNR,   0x00);  // Channel number.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCTRL1,  0x08);  // Freq synthesizer control.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCTRL0,  0x00);  // Freq synthesizer control.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ2,    0x5D);  // Freq control word, high byte
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ1,    0x44);  // Freq control word, mid byte.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ0,    0xEC);  // Freq control word, low byte.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG4,  0x86);  // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG3,  0x83);  // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG2,  0x03);  // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG1,  0x43);  // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG0,  0x38);  // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_DEVIATN,  0x44);  // Modem dev (when FSK mod en)
    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM2 ,   0x07);  // MainRadio Cntrl State Machine
    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM1 ,   0x3E);  // MainRadio Cntrl State Machine
    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM0 ,   0x18);  // MainRadio Cntrl State Machine
    TI_CC_SPIWriteReg(TI_CCxxx0_FOCCFG,   0x16);  // Freq Offset Compens. Config
    TI_CC_SPIWriteReg(TI_CCxxx0_BSCFG,    0x6C);  //  Bit synchronization config.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL2, 0x03);  // AGC control.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL1, 0x40);  // AGC control.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL0, 0x91);  // AGC control.
    TI_CC_SPIWriteReg(TI_CCxxx0_WOREVT1,  0x87);
    TI_CC_SPIWriteReg(TI_CCxxx0_WOREVT0,  0x6B);
    TI_CC_SPIWriteReg(TI_CCxxx0_WORCTRL,  0xF8);
    TI_CC_SPIWriteReg(TI_CCxxx0_FREND1,   0x56);  // Front end RX configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREND0,   0x10);  // Front end RX configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL3,   0xA9);  // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL2,   0x0A);  // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL1,   0x00);  // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL0,   0x11);  // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_RCCTRL1,  0x41);
    TI_CC_SPIWriteReg(TI_CCxxx0_RCCTRL0,  0x00);
    TI_CC_SPIWriteReg(TI_CCxxx0_FSTEST,   0x59);  // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_PTEST,    0x7F);
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCTEST,  0x3F);
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST2,    0x81);  // Various test settings.
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST1,    0x35);  // Various test settings.
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST0,    0x0B);  // Various test settings.
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
    delay_us(25);
    CC_CheckNoOfBytesinTXFIFO();
    delay_us(1);
    spi_write(STX);
    ReceiveValue = spi_read(SNOP);
    delay_us(1);
    spi_write(SFTX);
    ReceiveValue = spi_read(SNOP);
    delay_us(1);
    output_high(SPI_SS);
}



