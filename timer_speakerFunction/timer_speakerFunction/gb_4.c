/*
실험과정 8-4
3번에서 sound_set_frequency()함수의 동작을 확인했다면 OC3A핀으로 다음과 같은 신호를 무한 반복 출력하도록
while()루프에 들어갈 내용을 완성하여라.
320Hz와 480Hz를 80ms동안 8회 반복해서 출력하고 그 다음 1초 동안은 출력을 끄면서 이 과정 전체를 무한 반복한다. 
 */ 

/*
sound_set_frequency(), sound_mute(), _delay_ms() 함수를 사용하면 이 일을 할 수 있다. 
이제 J16에 스피커를 연결한 후 프로그램을 실행시켜 보아라. 
제대로 동작한다면 많이 들어본 소리를 들을 수 있을 것이다. 
스피커에서 소리가 잘 나오는 것을 확인했다면 이 코드는 앞으로 더 이상 사용하지 않는다
*/


#include "board.h"
#include "fnd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include "sound_gb.h"

static uint16_t fnd_num=0; //함수외부에 전역변수 선언해야함.

ISR(TIMER5_COMPA_vect)  //타이머5의 인터럽트를 설정한다. 
{
    fnd_write_numbers(fnd_num++);
    if(fnd_num==1000)
     fnd_num=0;
}

void ioport_init(void)
{
    DDRE=_BV(PE3); // 타이머3의 PE3을 출력으로 설정
    DDRB=_BV(PB5); //타이머5의 PB5를 출력으로 설정
}
void timer_init(void)
{
    TCCR3B|=_BV(WGM32); //타이머3:ctc모드로 설정 
    TCCR3A|=_BV(COM3A0); //oc3a핀을 toggle
    //실제로는 동작하지 않게 
    //timer3 enable 하는 코드인 TIMSK3=_BV(OCIE3A); 코드를 따로 작성하지 않으면 된다. 
     
    TCCR5B|=_BV(WGM52); //타이머5:ctc모드로 설정
    OCR5A|=(F_CPU/256/10)-1; //0.1초 간격으로 comparematch가 발생?? 
    TIMSK5|=_BV(OCIE5A); // timer5 enable
    
}
void interrupt_init(void)
{
    EICRA|=_BV(ISC31);  //하강모서리에서 INT3이 발생하도록 EICRA를 설정
    EICRB|=_BV(ISC71);  //하강모서리에서 INT7이 발생하도록 EICRB를 설정
    EIMSK|=_BV(INT3)|_BV(INT7); //INT3과 INT7을 enable시킨다. 
    sei();    //global interrupt flag를 set한다. 
}


int main(void)
{
   ioport_init();
   timer_init();
   interrupt_init();
  
  fnd_write_numbers(fnd_num);

    while (1) 
    {

    for(int inx=0;inx<8;inx++) //8번 반복한다.
    {
       sound_set_frequency(320); //320hz로 sound출력
       _delay_ms(80); //80ms 간격으로 
       sound_set_frequency(480); //480hz로 sound출력
       _delay_ms(80);
    }
     sound_mute();
     _delay_ms(1000);//1초동안은 출력을 끈다.
    
    }
}