 /*
예비 8-3
예비 8-4
예비 8-5
 */ 

/*
예비 8-4
16비트 길이의 변수 freq_hz를 인자로 받아서 그 주파수의 구형파를 OC3A핀으로 출력하는 일을
하는 함수 sound_set_frequency()를 작성하여라. 이때 Timer3의 prescaler는 8로 한다.
*/

/*
예비 8-5
4번에서 작성한 sound_set_frequency()함수는 구형파를 OC3A핀으로 출력하는 기능을 한다. 
이 함수를 호출한 후 구형파 출력을 중단하려고 할때 sound_mute()함수를 호출할 생각이다. 
다음 함수를 작성하여라. 






*/
#include "board.h"
#include "fnd.h"
#include <avr/io.h>

void sound_set_frequency(uint16_t freq_hz) //예비 8-4
{
    OCR3A=1000000/freq_hz-1; //OCR3A값 설정
    TCCR3B|=_BV(CS31)|_BV(WGM32); //Timer3의prescaler는 8로 한다.  
    //presacler와 관련된 비트 이외의 값을 바꾸지 않도록 주의해야한다. 
    
}

void sound_mute(void)
{
    TCCR3B &=0; //Timer3의 동작을 정지시키도록 레지스터를 설정한다.
    
    if(PINE&_BV(SOUND_OUT))
      TCCR3C=_BV(FOC3A); //
      
}