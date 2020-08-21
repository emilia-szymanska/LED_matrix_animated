#include<Arduino.h>
#define sbi(port, pin) (port) |= _BV(pin)
#define cbi(port, pin) (port) &= ~_BV(pin)
#define tbi(port, pin) (port) ^= _BV(pin)

int values[] = {0xF3, 0xE1, 0xC1, 0x83, 0x83, 0xC1, 0xE1, 0xF3};

void display(int shift)
{
  for(int j = 0; j < 8; j++)
  {
    if(j == 6 || j == 7) 
    {
      PORTB = 0x00;
      PORTC = (1<<(j%6));
    }
    else 
    {
      PORTC = 0x00;
      PORTB = (1<<j);
    }
    PORTD = ((values[j] <<shift)|(values[j]>>(8-shift)));
    _delay_ms(0.5);
    PORTC = 0x00;
  }
}


void setup()
{
  DDRD = 0xFF;  //rows
  DDRB = 0xFF;  //columns
  DDRC = 0xFF;  //columns
  PORTD = 0x00;
  PORTB = 0x00;
  PORTC = 0xFF;
}

int main()
{
  setup();
  while(1)
  {
    for(int i = 0; i < 8; i++)
    {
      for(int j = 0; j < 100; j++)
      {
        display(i);
      } 
    }
  }
}
