const int pingPin = 3; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 2; // Echo Pin of Ultrasonic Sensor

volatile long duration; // Declare duration as a volatile variable to use it in the interrupt service routine
volatile bool pulseDetected = false; // Declare a flag to indicate when a pulse has been detected

void setup()
{
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(echoPin), pulseDetectedISR, CHANGE); // Attach an interrupt to the echo pin
}

void loop() {
  long cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  
  while (!pulseDetected) {
    // Wait for the interrupt to trigger
  }
  pulseDetected = false; // Reset the flag

  cm = microsecondsToCentimeters(duration);
  
  if (cm > 2 && cm <100)
  {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(8, HIGH);
    tone(7, 220, 100);
    delay(100);
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
  
  Serial.print("Distance :");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(800);
}

void pulseDetectedISR() {
  if (digitalRead(echoPin) == HIGH) {
    duration = micros(); // Record the start time of the pulse
  } else {
    duration = micros() - duration; // Calculate the duration of the pulse
    pulseDetected = true; // Set the flag to indicate that a pulse has been detected
  }
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
