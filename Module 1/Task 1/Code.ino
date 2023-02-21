
const int pingPin = 3; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 2; // Echo Pin of Ultrasonic Sensor

void setup()
{
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop() {
   long duration, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
  
   digitalWrite(pingPin, HIGH);
  
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
  
  if (cm > 2 && cm <100)
  {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(8, HIGH);
    tone(7, 220, 100);
    delay(200);
  }
  
  if (cm >101 && cm < 300)
  {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(8, LOW);
  }
  
  if (cm > 300)
  {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(8, LOW);
  }
   Serial.print("Distance : ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(800);
}


long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
