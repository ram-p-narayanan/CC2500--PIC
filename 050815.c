#include <18F24J11.h>
#include <CC_Wireless.h>
#include <SHT11.h>
#include <Init.h>
#include <SendData_To_Transmit.h>

/*This program will sense the Humidity and Temperature by the help od a SHT11
 *Sensor. The manipulated final result is transmitted wirelessly for every
 *20 seconds as of not. The time is generated with the help of a Timer Interrupt.
 **/

#INT_TIMER1
Timer1_Overflow()
{
    //set_timer1(T1_DISABLED);
    ++Timer1_Flag;
    if(Timer1_Flag > 100)
    {
        Timer1_Flag = 0;
        printf("Timer Interrupt Occured \r");
        printf("Temp : %3.1f C \r  ", restemp);
        Send_to_Tx();
    }
    //setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
    set_timer1(0);
}

void main()
{
    printf("Start Of Operation \r");
    Init_Peripherals_Interrupts_Functions();
    while(1)
    {
        sht_rd (restemp, truehumid);
        printf("Temp : %3.1f C \r  ", restemp);
        printf("\nRH   : %3.1f %% \r\r   ", truehumid);
        delay_ms(1000);        //delay 500 ms between reading to prevent self heating of sensor
    }
}