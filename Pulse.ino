/* Pulse))) Parking SEnsor

   This sketch uses a PING))) ultrasonic sensor to detect if
   a car is correctly parked in a garage.

   This operates as follows, if the ultrassonic sensor detects a 
   vehicle in range, it turns on a red light and starts beeping 
   in order to alert that the vehicle should not move further. 
   If no vehicle is detected a green light is turned on and no
   beeping is produced.

   Operation Example:
   (W - Wall, S - Sensor, G - Garage Door, V - Vehicle)
   
   W _ S _ _ G (Empty Garage)           Green On, Red & Buzzer Off
   W _ S _ V G (Vehicle Parked OK)      Green On, Red & Buzzer Off
   W _ S V _ G (Vehicle Parked OK)      Green On, Red & Buzzer Off
   W _ V _ _ G (Vehicle Below Sensor)   Green Off, Red & Buzzer On
   W V S _ _ G (Vehicle Crossed Sensor) Green Off, Red & Buzzer On

   Important:   
   In this sketch we assume that the vehicle fits between the
   sensor and the garage door.

   The ultrasonic sensor must be placed on the ceiling and in
   the opposite side of a garage door.   

   You have to change constant RANGE_OK, that represents the
   distance between the ceiling and the floor, to the desired 
   value.
   
   The circuit:
	* +V connection of the PING))) attached to +5V
	* GND connection of the PING))) attached to ground
	* TRIG connection of the PING))) attached to digital pin 22
	* ECHO connection of the PING))) attached to digital pin 23
	* +BUZZER connection of the buzzer attached to digital pin 24
	* -BUZZER connection of the buzzer attached to ground
	* R1 270 Ohm connection of resistor attached to digital pin 25
	* +LED connection of green led attached to resistor R1
	* -LED connection of green led attached to ground
	* R2 330 Ohm connection of resistor attached to digital pin 26
	* +LED connection of red led attached to resistor R2
	* -LED connection of red led attached to ground

   Note that instead of using only one LED for each light you can
   use relays to trigger sources that need more than 5v.
   (e.g. 12v DC led strip, 12v DC horn) 
   (see http://playground.arduino.cc/uploads/Learning/relays.pdf)
     
   created by Tiago Santos

 */

// uncomment for debugging the distance
// obtained by the sensor
//#define DEBUG

const int PING_TRIG_PIN = 22;
const int PING_ECHO_PIN = 23;
const int BUZZER_PIN = 24;
const int GREEN_PIN = 25;
const int RED_PIN = 26;
const char RANGE_OK = 180;//185
const char OFF = 0;
const char RED = 1;
const char GREEN = 2;
const long BEEP_INTERVAL = 2000;

char currState = OFF;
unsigned long prevTime = 0;
unsigned long beepTimer = 0;
bool beeping = false;
int buzzerState = LOW;

void setup() {
  #ifdef DEBUG
  // initialize serial communication:
  Serial.begin(9600);
  #endif

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PING_TRIG_PIN, OUTPUT);
  pinMode(PING_ECHO_PIN, INPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
}

void loop() {
  // establish variables for duration of the ping,
  // and the distance result in centimeters:
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more 
  // microseconds. Give a short LOW pulse beforehand to 
  // ensure a clean HIGH pulse:
  digitalWrite(PING_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(PING_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(PING_TRIG_PIN, LOW);

  // read the signal from the PING))): a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(PING_ECHO_PIN, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  if (cm < RANGE_OK) {
    // Something detected
    // change state to red
    currState = RED;
  } else {
    // Nothing detected
    // change state to green
    currState = GREEN;
  }

  int greenState = LOW;
  int redState = LOW;
  
  switch (currState) {
    case RED:
      if (!beeping) {
        beepTimer = 0; // not beeping ok start
        beeping = true;
        buzzerState = HIGH;
      }
      redState = HIGH;
      break;
    case GREEN:
      beeping = false; // don't beep on green
      buzzerState = LOW;
      greenState = HIGH;
      break;
    case OFF: 
      beeping = false; // don't beep when off
      buzzerState = LOW;
    default: break;
  }

  unsigned long currentMillis = millis();

  if (beeping && (currentMillis - beepTimer >= BEEP_INTERVAL)) {
    beepTimer = currentMillis;
    if (buzzerState == LOW) buzzerState = HIGH;
    else buzzerState = LOW;
  }

  digitalWrite(BUZZER_PIN, buzzerState);  
  digitalWrite(GREEN_PIN, greenState);
  digitalWrite(RED_PIN, redState);

  #ifdef DEBUG  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  #endif

  delay(100);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per 
  // centimeter. The ping travels out and back, so to find 
  // the distance of the object we take half of the distance
  // travelled. So the result would be microseconds/ 29 / 2,
  // or by doing some extra math, microseconds / 58.
  return microseconds / 58;
}
