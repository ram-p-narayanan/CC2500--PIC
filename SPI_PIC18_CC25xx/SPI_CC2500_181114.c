#include <pic18.h>
#include "spi_header.h"

char paTable[] = {0xFB};
char paTableLen = Enable;
static unsigned char ReturnValue;

void main(void)
{
	PIC_Port_Initialize();
	SPI_Register_Initialize();
        delay(2);
	SS = Enable;
        delay(2);
        SS = Disable;
	OpenSPI1(SPI_FOSC_16,0x01,0x01);
	SPI_WriteRFSettings();
	SPI_CheckStatus();
        SS = Enable;
	while(1);
}


void SPI_CheckStatus()
{	
	//SS = Disable;
	
	WriteSPI1(TI_CCxxx0_PARTNUM);
	WriteSPI1(TI_CCxxx0_DUMMY);
	ReturnValue = ReadSPI1();
	
	WriteSPI1(TI_CCxxx0_VERSION);
	WriteSPI1(TI_CCxxx0_DUMMY);
	ReturnValue = ReadSPI1();
	
	WriteSPI1(TI_CCxxx0_SIDLE);
	WriteSPI1(TI_CCxxx0_SNOP);
	ReturnValue = ReadSPI1();
	
	//SS = Enable;
}	
void PIC_Port_Initialize(void)
{

   LATB = Disable; TRISB  = Disable; PORTB = Disable;
   LATC = Disable; TRISC  = Disable; PORTC = Disable;
   // Let the Interrupt Pins be in the default state. 
}

void SPI_Register_Initialize(void)
{
    //SS_Dir = Disable;                            // Chip Select
    ANCON1bits.PCFG11   = Enable;
    TRISCbits.TRISC0 	= Disable;	TRISCbits.TRISC1 = Disable;
    TRISCbits.TRISC2 	= Disable;
    PORTCbits.RC0    	= Enable;	PORTCbits.RC1    = Enable;
    	SDO1_Dir        = Disable;
	SDI1_Dir  	= Enable;
	SCK1_Dir  	= Disable; 
	PORTCbits.RC2 	= Enable;
	NOP();
}

unsigned char ReadSPI1( void )
{
  unsigned char TempVar;
  TempVar = SSP1BUF;       //Clear BF
  PIR1bits.SSP1IF = Disable;     //Clear interrupt flag
  SSP1BUF = 0x00;          // initiate bus cycle
  //while ( !SSP1STATbits.BF );                // wait until cycle complete
  while(!PIR1bits.SSP1IF); //wait until cycle complete
  return ( SSP1BUF );      // return with byte read
}

signed char WriteSPI1( unsigned char data_out )
{
  unsigned char TempVar;
  TempVar = SSP1BUF;           // Clears BF
  PIR1bits.SSP1IF = Disable;         // Clear interrupt flag
  SSP1CON1bits.WCOL = Disable;			//Clear any previous write collision
  SSP1BUF = data_out;          // write byte to SSP1BUF register
  if ( SSP1CON1 & 0x80 )       // test if write collision occurred
   return ( -1 );              // if WCOL bit is set return negative #
  else
   //while( !SSP1STATbits.BF ); // wait until bus cycle complete
   while(!PIR1bits.SSP1IF); // wait until bus cycle complete
  return ( 0 );                // if WCOL bit is not set return non-negative#
}

void OpenSPI1( unsigned char sync_mode, unsigned char bus_mode, unsigned char smp_phase)
{
  SSP1STAT &= 0x3F;               // power on state
  SSP1CON1 = 0x00;                // power on state
  SSP1CON1 |= sync_mode;          // select serial mode
  SSP1STAT |= smp_phase;          // select data input sample phase

  switch( bus_mode )
  {
    case 0:                       // SPI1 bus mode 0,0
        SSP1STATbits.CKE = Disable;       // data transmitted on Rising edge
        SSP1CON1bits.CKP = Disable; 		// clock idle state low
      break;
	case 1:                       // SPI1 bus mode 0,1
        SSP1STATbits.CKE = Disable;       // data transmitted on falling edge
	SSP1CON1bits.CKP = Enable;			// clock idle state high
      break;
    case 2:                       // SPI1 bus mode 1,0
        SSP1STATbits.CKE = Enable;       // data transmitted on falling edge
        SSP1CON1bits.CKP = Disable;       // clock idle state low
      break;
    default:                      // default SPI1 bus mode 0,1
	SSP1STATbits.CKE = Enable;       // data transmitted on rising edge
        SSP1CON1bits.CKP = Enable;       // clock idle state high
      break;
  }

	TRISCbits.TRISC3 = Disable;       // define clock pin as output
       	TRISCbits.TRISC4 = Enable;       // define SDI pin as input
	TRISCbits.TRISC5 = Disable;       // define SDO pin as output

	SS = Disable;
        SSP1CON1 |= SSPENB;             	// enable synchronous serial port
 }

void SPI_WriteRFSettings(void)
{
	// Write register settings
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG2,   0x0B);  // GDO2 output pin config.
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG0,   0x06);  // GDO0 output pin config.
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTLEN,   0xFF);  // Packet length.
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTCTRL1, 0x05);  // Packet automation control.
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTCTRL0, 0x05);  // Packet automation control.
    TI_CC_SPIWriteReg(TI_CCxxx0_ADDR,     0x01);  // Device address.
    TI_CC_SPIWriteReg(TI_CCxxx0_CHANNR,   0x00); // Channel number.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCTRL1,  0x07); // Freq synthesizer control.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCTRL0,  0x00); // Freq synthesizer control.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ2,    0x5D); // Freq control word, high byte
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ1,    0x93); // Freq control word, mid byte.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ0,    0xB1); // Freq control word, low byte.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG4,  0x2D); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG3,  0x3B); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG2,  0x73); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG1,  0x22); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG0,  0xF8); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_DEVIATN,  0x00); // Modem dev (when FSK mod en)
    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM1 ,   0x3F); //MainRadio Cntrl State Machine
    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM0 ,   0x18); //MainRadio Cntrl State Machine
    TI_CC_SPIWriteReg(TI_CCxxx0_FOCCFG,   0x1D); // Freq Offset Compens. Config
    TI_CC_SPIWriteReg(TI_CCxxx0_BSCFG,    0x1C); //  Bit synchronization config.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL2, 0xC7); // AGC control.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL1, 0x00); // AGC control.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL0, 0xB2); // AGC control.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREND1,   0xB6); // Front end RX configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREND0,   0x10); // Front end RX configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL3,   0xEA); // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL2,   0x0A); // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL1,   0x00); // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL0,   0x11); // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_FSTEST,   0x59); // Frequency synthesizer cal.
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST2,    0x88); // Various test settings.
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST1,    0x31); // Various test settings.
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST0,    0x0B);  // Various test settings.
}


void TI_CC_SPIWriteReg(char addr, char value)
{
	static signed char AckReturn;
	//SS = Disable;
	AckReturn = WriteSPI1(addr);
		while(AckReturn) {}
	AckReturn = WriteSPI1(value);
		while(AckReturn) {}
	//SS = Enable;
}

void delay(unsigned int DelayTime)
{
    unsigned int TempVariable;
    while(DelayTime)
    {
        --DelayTime;
        for(TempVariable = 0; TempVariable <= DelayTime; TempVariable++);
    }
}