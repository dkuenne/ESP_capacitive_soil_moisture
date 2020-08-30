/*

  ESP capacitive soil moisture sensor
  >>> Petersilie <<<

  Version:
  v0.1

  Uses code from:
  - how2electronics.com: Example code for sensor and LCD (https://how2electronics.com/interface-capacitive-soil-moisture-sensor-arduino/)
  - tandembyte/LCD_I2C: Library (https://gitlab.com/tandembyte/LCD_I2C/-/tree/master)
  Please see LICENSE file for details.

  Notes:
  - Needs to be calibrated for every sensor / ESP combination
  - Probably needs to be calibrated for different power sources
  
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// Default address 0x27, 20 chars, 4 lines
LiquidCrystal_I2C lcd(0x27,20,4);


int airVal = 684;
int waterVal = 312;
const int sensorPin = A0;
int measuredVal = 0;
int highestVal = 0;
int lowestVal = 30000;
int soilMoisturePercent = 0;
int previousSoilMoisturePercent = 0;
bool WlanOnline = false;


// Custom symbols for WLAN connection
byte wlanSym[8] = {

  0b00000,
  0b00000,
  0b00000,
  0b11100,
  0b00010,
  0b11001,
  0b00101,
  0b10101

};

byte wlanSymOk[8] = {

  0b00000,
  0b00000,
  0b00000,
  0b00001,
  0b00001,
  0b10010,
  0b01010,
  0b00100

};

byte wlanSymErr[8] = {

  0b00000,
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100,
  0b01010,
  0b10001

};


void setup() {
  
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  lcd.createChar(8, wlanSym);
  lcd.createChar(9, wlanSymOk);
  lcd.createChar(10, wlanSymErr);

}



void loop() {

  // Print edges top left and down right
  lcd.setCursor(0,0);
  lcd.write(0xA2);
  lcd.setCursor(19,3);
  lcd.write(0xA3);

  lcd.setCursor(3,0);
  lcd.print("# Petersilie #");
  
  // Measure air value (0%) to calibrate
  //measureAir();

  // Measure water value (100%) to calibrate
  //measureWater();

  // Measure and display current values
  measureSoil();

  // Raw values for debugging purposes
  //rawVals();

  delay(250);
  
}



void measureSoil(){

  measuredVal = analogRead(sensorPin);
  soilMoisturePercent = map(measuredVal, airVal, waterVal, 0, 100);

  if(soilMoisturePercent > 100){

    // Debug
    //Serial.println("Error: Moisture too high! Please calibrate.");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ERROR");
    lcd.setCursor(0,1);
    lcd.print("PLEASE RECALIBRATE");

  }

  else if(soilMoisturePercent < 0){

    // Debug
    //Serial.println("Error: Moisture too low! Please calibrate.");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ERROR");
    lcd.setCursor(0,1);
    lcd.print("PLEASE RECALIBRATE");

  }

  else if(soilMoisturePercent <= 100 && soilMoisturePercent >= 0){

    // Debug
    //Serial.print("Feuchtigkeit: ");
    //Serial.print(soilMoisturePercent);
    //Serial.println(" %");

    if(soilMoisturePercent != previousSoilMoisturePercent){

      lcd.setCursor(4,1);
      lcd.print("Feuchtigkeit");
      // Clear line
      lcd.setCursor(0,2);
      lcd.print("                   ");
      
      lcd.setCursor(8,2);
      lcd.print(soilMoisturePercent);
      lcd.print(" %");

      previousSoilMoisturePercent = soilMoisturePercent;
      
    }

  }

  if (WlanOnline == true){

    lcd.setCursor(0,3);
    lcd.write((byte)8);
    lcd.write((byte)9);
    
  }

  else{

    lcd.setCursor(0,3);
    lcd.write((byte)8);
    lcd.write((byte)10);

  }

}



void rawVals(){

  measuredVal = analogRead(sensorPin);

  Serial.print("Current value: ");
  Serial.println(measuredVal);

  delay(250);
  
}



void measureAir(){

  measuredVal = analogRead(sensorPin);
  
  if (measuredVal > highestVal){

    highestVal = measuredVal;

  }
  
  Serial.print("Highest current AIR value: ");
  Serial.println(highestVal);

  delay(250);
  
}



void measureWater(){

  measuredVal = analogRead(sensorPin);
  
  if (measuredVal < lowestVal){

    lowestVal = measuredVal;

  }
  
  Serial.print("Lowest current WATER value: ");
  Serial.println(lowestVal);

}