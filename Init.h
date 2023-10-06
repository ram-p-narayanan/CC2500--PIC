void Init_Peripherals_Interrupts_Functions();
void SHT_Init();
void RF_Init();
void Interrupt_Init();

void Init_Peripherals_Interrupts_Functions()
{
    RF_Init();
    SHT_Init();
    Interrupt_Init();
}

void SHT_Init (void)
{
    comreset();    //reset SHT75
    delay_ms(20);  //delay for power-up
}

void RF_Init()
{
    setup_adc_ports(ADC_OFF);
    setup_adc(NO_ANALOGS);
    setup_adc(ADC_OFF);
    output_high(SPI_SS);  // Initial Slave Select to a high level
    setup_spi(SPI_MASTER | SPI_MODE_0 | SPI_CLK_DIV_64);
    CC_SetIdleMode();
    CC_WriteRFSettings();
}
void Interrupt_Init()
{
 enable_interrupts(GLOBAL);
 enable_interrupts(INT_TIMER1);
 set_timer1(0);
 setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
}
