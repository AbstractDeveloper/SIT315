const int pingPin = 3; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 2; // Echo Pin of Ultrasonic Sensor

volatile long duration; // Declare duration as a volatile variable to use it in the interrupt service routine
volatile bool pulseDetected = false; // Declare a flag to indicate when a pulse has been detected

int baselineTemp = 0;
int celsius = 0;
int sensorState = 0;
int fahrenheit = 0;

void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(echoPin), pulseDetectedISR, CHANGE); // Attach an interrupt to the echo pin
}

void loop()
{

  // ****FOR TEMPERATURE SENSOR****
  // set threshold temperature to activate LEDs
  baselineTemp = 30;
  // measure temperature in Celsius
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);

  // convert to Fahrenheit
  fahrenheit = ((celsius * 9) / 5 + 32);
  Serial.print("Temperature : ");
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(fahrenheit);
  Serial.println(" F");

  if (celsius < baselineTemp) {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }

  if (celsius >= baselineTemp && celsius < baselineTemp + 40) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  }
  if (celsius >= baselineTemp + 30) {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    tone(8, 220, 100);
  }
  delay(400);

  // ****FOR ULTRASONIC SENSOR****

  long duration, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);

  digitalWrite(pingPin, HIGH);

  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);

  while (!pulseDetected) {
    // Wait for the interrupt to trigger
  }
  pulseDetected = false; // Reset the flag

  cm = microsecondsToCentimeters(duration);

  if (cm > 2 && cm < 100)
  {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    tone(8, 220, 100);
    delay(200);
  }

  if (cm > 101 && cm < 300)
  {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  }

  if (cm > 300)
  {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  Serial.print("Distance : ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(400);
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
