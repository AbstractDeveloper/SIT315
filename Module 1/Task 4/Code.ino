int LED_1 = 8;         // First LED pin set to a variable
int SENSOR_1 = 2;       // First PIR sensor set to a variable
int LED_2 = 9;         // Second LED pin set to a variable
int SENSOR_2 = 3;      // Second PIR sensor set to a variable
int LED_3 = 10;        // Third LED pin number to a variable
int SOIL_SENSOR_3 = 4; // Soil Moisture sensor set to a variable
int LED_4 = 11;        // Fourth LED pin number to a variable

volatile bool ledstatus_1 = false;
volatile bool ledstatus_2 =false;
volatile bool ledstatus_3 =false;

void starttimmerfunc()
{
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1=0;
  OCR1A = 31249;
  TCCR1B |= (1<<WGM12);
  TCCR1B |= (1 << CS12) | (0<<CS11)| (1<<CS10);
  TIMSK1 |= (1<<OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
  digitalWrite(LED_4,digitalRead(LED_4) ^ 1);
  Serial.println("LED Timer : 2 seconds ");
}

void setup() {
  pinMode(LED_1, OUTPUT);    // set the first LED pin as an output
  pinMode(SENSOR_1, INPUT);   // set the first PIR sensor pin as an input
  
  pinMode(LED_2, OUTPUT);    // set the second LED pin as an output
  pinMode(SENSOR_2, INPUT);   // set the second PIR sensor pin as an input
  
  pinMode(LED_3, OUTPUT);    // set the third LED pin as an output
  pinMode(SOIL_SENSOR_3, INPUT); // set the soil moisture sensor pin as an input
  
  pinMode(LED_4, OUTPUT);  // set the fourth LED pin as an output
  
  starttimmerfunc();   // To start the timer function
  
  Serial.begin(9600);         // initialize serial communication at 9600 baud
  
  noInterrupts();
  PCIFR |= bit(PCIE2);
  PCICR |= bit(PCIE2);
  PCMSK2 |= bit (PCINT18);
  PCMSK2 |= bit (PCINT19);
  PCMSK2 |= bit (PCINT20);
  interrupts();
}

void loop() { }  // nothing to do in the loop function

ISR(PCINT2_vect)
{
  if(digitalRead(SENSOR_1) == HIGH)
    {
       ledstatus_1 = !ledstatus_1;
      digitalWrite(LED_1,ledstatus_1);
      Serial.println("Sensor 1 Interrupted");
    }
  if(digitalRead(SENSOR_2) == HIGH)
    {
       ledstatus_2 = !ledstatus_2;
      digitalWrite(LED_2,ledstatus_2);
      Serial.println("Sensor 2 Interrupted");
    }
  if(digitalRead(SOIL_SENSOR_3) == HIGH)
    {
       ledstatus_3 = !ledstatus_3;
      digitalWrite(LED_3,ledstatus_3);
      Serial.println("Sensor 3 Interrupted");
    }
}
