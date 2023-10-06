#use delay(clock=4000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
#fuses HS,NOWDT,NOPROTECT


#define E1 PIN_B2
#define E2 PIN_B3
#define E3 PIN_B4
#define E4 PIN_B5
#define E5 PIN_C0
#define E6 PIN_C1

#define D0 PIN_A0
#define D1 PIN_A1
#define D2 PIN_A2
#define D3 PIN_A3

void uC_Init();
void GPIO_Init();
void Data_Lines_Init();
void Enable_Func_Check();

void enable_E1()
{
    output_low(E1);
    output_high(E2);
    output_high(E3);
    output_high(E4);
    output_high(E5);
    output_high(E6);  
}

void enable_E2()
{
    output_high(E1);
    output_low(E2);
    output_high(E3);
    output_high(E4);
    output_high(E5);
    output_high(E6);
}

void enable_E3()
{
    output_high(E1);
    output_high(E2);
    output_low(E3);
    output_high(E4);
    output_high(E5);
    output_high(E6);
}

void enable_E4()
{
    output_high(E1);
    output_high(E2);
    output_high(E3);
    output_low(E4);
    output_high(E5);
    output_high(E6);
}

void enable_E5()
{
    output_high(E1);
    output_high(E2);
    output_high(E3);
    output_high(E4);
    output_low(E5);
    output_high(E6);
}

void enable_E6()
{
    output_high(E1);
    output_high(E2);
    output_high(E3);
    output_high(E4);
    output_high(E5);
    output_low(E6);
}

void Data_Lines_Init()
{
    output_high(D0);
    output_high(D1);
    output_high(D2);
    output_high(D3);
}

void Write0()
{
    output_low(D0);
    output_low(D1);
    output_low(D2);
    output_low(D3);
}
void Write1()
{
    output_high(D0);
    output_low(D1);
    output_low(D2);
    output_low(D3);
}

void Write2()
{
    output_low(D0);
    output_high(D1);
    output_low(D2);
    output_low(D3);
}

void Write3()
{
    output_high(D0);
    output_high(D1);
    output_low(D2);
    output_low(D3);
}

void Write4()
{
    output_low(D0);
    output_low(D1);
    output_high(D2);
    output_low(D3);
}

void Write5()
{
    output_high(D0);
    output_low(D1);
    output_high(D2);
    output_low(D3);
}

void Write6()
{
    output_low(D0);
    output_high(D1);
    output_high(D2);
    output_low(D3);
}

void Write7()
{
    output_high(D0);
    output_high(D1);
    output_high(D2);
    output_low(D3);
}

void Write8()
{
    output_low(D0);
    output_low(D1);
    output_low(D2);
    output_high(D3);
}

void Write9()
{
    output_high(D0);
    output_low(D1);
    output_low(D2);
    output_high(D3);
}

void Blank()
{
    output_high(D0);
    output_high(D1);
    output_high(D2);
    output_high(D3);
}

void Write(int digit)
{
    if (digit == 0) Write0();
    else if (digit == 1) Write1();
    else if (digit == 2) Write2();
    else if (digit == 3) Write3();
    else if (digit == 4) Write4();
    else if (digit == 5) Write5();
    else if (digit == 6) Write6();
    else if (digit == 7) Write7();
    else if (digit == 8) Write8();
    else if (digit == 9) Write9();
    else Blank();
    delay_ms(5);
}

void Enable(int digit)
{
    if (digit == 1) enable_E1();
    else if (digit == 2) enable_E2();
    else if (digit == 3) enable_E3();
    else if (digit == 4) enable_E4();
    else if (digit == 5) enable_E5();
    else if (digit == 6) enable_E6();
    delay_ms(5);
}

void Disable_All()
{
    output_high(E1);
    output_high(E2);
    output_high(E3);
    output_high(E4);
    output_high(E5);
    output_high(E6);
    delay_ms(5);
}

void EnablenBlank()
{
    Enable(1);
    delay_ms(5);
    Blank();
    delay_ms(5);
    Enable(2);
    delay_ms(5);
    Blank();
    delay_ms(5);
    Enable(3);
    delay_ms(5);
    Blank();
    delay_ms(5);
    Enable(4);
    delay_ms(5);
    Blank();
    delay_ms(5);
    Enable(5);
    delay_ms(5);
    Blank();
    delay_ms(5);
    Enable(6);
    delay_ms(5);
    Blank();
    delay_ms(5);
}

void GPIO_Init()
{
    output_high(E1);
    output_high(E2);
    output_high(E3);
    output_high(E4);
    output_high(E5);
    output_high(E6);
    output_high(D0);
    output_high(D1);
    output_high(D2);
    output_high(D3);
}

void uC_Init()
{
    disable_interrupts(GLOBAL);
    setup_adc_ports(ADC_OFF);
    setup_adc(NO_ANALOGS);
    setup_adc(ADC_OFF);
}
