 /*
MPS20N0040D Pressure Sensor test Code
 */

const int analogInPin = A0;  // Sensor conditioned Signal connected to A0
int sensorValue = 0;        // value read from the pressure sensor via the amplifier stage
float sensorVoltage = 0;    // Value of equivalent voltage
float PressureValue = 0;      // value output to the Serial port
float rho = 997; //kg/m^2 density of liquid
float specificWeight = 9780; // N/m^3 rho*g
float level = 0; // m height
float bubblerValue = 0; //uncalibrated height values obtained
float pressurePascal = 0; //pressure in pascal

const int ledCount = 10;    // the number of LEDs in the bar graph
int ledLevel = 0;
int ledPins[] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11
};   // an array of pin numbers to which LEDs are attached

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  // loop over the pin array and set them all to output:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  } 
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  
  // print the results to the serial monitor:
  Serial.print("Sensor ADC bits = " );                       
  Serial.print(sensorValue); 
  Serial.print(";  " );   

  //Equivalent Voltage Value
  sensorVoltage = sensorValue*(5.0/1023.0);
  Serial.print("Sensor Voltage = " );                       
  Serial.print(sensorVoltage);
  Serial.print(";  " );  

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////

  //Calibration of Pressure Measurement
  //Mapping the range of pressure to range of ADC bits
  PressureValue = map(sensorValue, 21, 405, 0, 70);  // demo for pressure 
  //PressureValue = map(sensorValue, 21, 122, 0, 20);  // demo for level (recalibrate) 

  Serial.print("Pressure = " );                       
  Serial.print(PressureValue);
  Serial.print(" mmHg" );
  Serial.print(";  " ); 

  //Pressure in Pascal                     
  pressurePascal = PressureValue*133.322;

  // /*
  //Level Measurement
  bubblerValue = (pressurePascal/specificWeight)*100; //height of the liquid in cm
  
  //Calibration of Level Measurement
  //Have Scale of 0-15cm
  
  level = map(bubblerValue, 0, 27, 0, 25);  // change 27 by calculation
  
  Serial.print("Height = " );                       
  Serial.print(level);
  Serial.print(" cm" ); 
  // */

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  
  // /*
  //Level Indicator on Bar Graph
  // map the result to a range from 0 to the number of LEDs:
  ledLevel = map(PressureValue, 0, 70, 0, ledCount);

  // loop over the LED array:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    // if the array element's index is less than ledLevel,
    // turn the pin for this element on:
    if (thisLed < ledLevel) {
      digitalWrite(ledPins[thisLed], HIGH);
    }
    // turn off all pins higher than the ledLevel:
    else {
      digitalWrite(ledPins[thisLed], LOW);
    }
  }
  // */

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  
  Serial.println();     
  delay(1000);                     
}
