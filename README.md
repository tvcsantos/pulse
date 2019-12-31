# Pulse
This is Pulse an Arduino Parking Sensor. It uses an ultrassonic sensor to dected if a car is correctly parked in a garage.

# Operation

If the ultrassonic sensor detects a vehicle in range, it turns on a red light and starts beeping in order to alert that the vehicle should not move further. If no vehicle is detected a green light is turned on and no beeping is produced.

## Example
  (W - Wall, S - Sensor, G - Garage Door, V - Vehicle)
  
   
  W _ S _ _ G (Empty Garage)           Green On, Red & Buzzer Off
  
  W _ S _ V G (Vehicle Parked OK)      Green On, Red & Buzzer Off
  
  W _ S V _ G (Vehicle Parked OK)      Green On, Red & Buzzer Off
  
  W _ V _ _ G (Vehicle Below Sensor)   Green Off, Red & Buzzer On
  
  W V S _ _ G (Vehicle Crossed Sensor) Green Off, Red & Buzzer On

# Important
In this sketch we assume that the vehicle fits between the sensor and the garage door.

The ultrasonic sensor must be placed on the ceiling and in the opposite side of the garage door.   

You have to change constant `RANGE_OK`, that representes the distance between the ceiling and the floor, to the desired value. Also we have used an Arduino Mega 2560, so if you use another board you have to change pin numbers accordingly.

# Circuit
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

Note that instead of using only one LED for each light you can use relays to trigger sources that need more than 5v. (e.g. 12v DC led strip, 12v DC horn). For more information on how to connect relays to arduino please see http://playground.arduino.cc/uploads/Learning/relays.pdf


## Copyright

Pulse is provided Copyright © 2016 under LGPL License.
