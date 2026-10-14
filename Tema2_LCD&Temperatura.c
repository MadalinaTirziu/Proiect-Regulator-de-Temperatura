#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int senzor = A0;

volatile int secunde = 0;
volatile int minute = 0;
volatile int ore = 12;

ISR(TIMER1_COMPA_vect) 
{
  secunde++;
  if (secunde >= 60) 
  {
    secunde = 0;
    minute++;
    
    if (minute >= 60) 
    {
      minute = 0;
      ore++;
      
      if (ore >= 24) 
      {
        ore = 0;
      }
    }
  }
}

void setup()
{
  lcd.begin(2, 16);
  cli();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 15624;

  TCCR1B |= (1 << WGM12); 
  TCCR1B |= (1 << CS12) | (1 << CS10);

  TIMSK1 |= (1 << OCIE1A);

  sei();
}

void loop()
{
  int valoare = analogRead(senzor);
  float tensiune = valoare * (5.0 / 1023.0);
  float temperatura = (tensiune - 0.5) * 100;
  
  lcd.setCursor(0, 0);
  lcd.print("Temp = ");
  
  lcd.print(temperatura);
  lcd.print("°C");
  
  lcd.setCursor(0, 1);
  lcd.print("Ora: ");

  if (ore < 10) lcd.print('0');
  lcd.print(ore);
  lcd.print(':');

  if (minute < 10) lcd.print('0');
  lcd.print(minute);
  lcd.print(':');

  if (secunde < 10) lcd.print('0');
  lcd.print(secunde);

  lcd.print("   ");
  
  delay(1000);
  	
}