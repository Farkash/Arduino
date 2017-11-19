//in C, when including files as sources, you often will use header files,
//which contain functions for example They are libraries essentially.
#include <Adafruit_BMP085_U.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal.h>

//You can set up global variables here:
//create an object/variable of type LiquidCrystal, call it lcd
//then tell it what pins to reference
LiquidCrystal lcd(11,12,4,5,6,7);

//create an object of the type created in the library. Name it bmp
//then assign it some sort of id?
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

int ledStormy = 8;
int ledRainy = 9;
int ledChange = 10;


void displaySensorDetails()
{
  sensor_t sensor;
  bmp.getSensor(&sensor);
//  lcd.print("------------------------------------");
  lcd.print  ("Sensor:       "); lcd.print(sensor.name);
  lcd.print  ("Driver Ver:   "); lcd.print(sensor.version);
  lcd.print  ("Unique ID:    "); lcd.print(sensor.sensor_id);
  lcd.print  ("Max Value:    "); lcd.print(sensor.max_value); lcd.print(" hPa");
  lcd.print  ("Min Value:    "); lcd.print(sensor.min_value); lcd.print(" hPa");
  lcd.print  ("Resolution:   "); lcd.print(sensor.resolution); lcd.print(" hPa");  
  lcd.print("------------------------------------");
  lcd.print("");
  delay(500);
}

void greeting() {
    lcd.print("Hello Dad.");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("This is your");
  delay(1000);
  lcd.clear();
  lcd.print("electronic");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("barometer.");
  delay(2000);
  lcd.clear();
  delay(1000);
}

//the void command is used here to indicate that the following 
//function will not return anything. 
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
//  lcd.print("Pressure Sensor Test"); 
  
  /* Initialise the sensor */
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    lcd.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  /* Display some basic information on this sensor */
//  displaySensorDetails();
}

void loop() {
  sensors_event_t event;
  bmp.getEvent(&event);

  greeting();
 
  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure)
  {
    /* Display atmospheric pressue in hPa, hectopascals, which is 100Pa
    A Pascal is 1N (Newton, the standard unit of force) per square meter
    1 hPa = 0.01450377 psi */
//    lcd.print("Atmos Pressure: ");
//    lcd.setCursor(0,1);
//    lcd.print(String(event.pressure) + " hPa");
//    delay(2000);
//    lcd.clear();
//    delay(500);

    lcd.print("Atmospheric");
    lcd.setCursor(0,1);
    lcd.print("Pressure:");
    delay(2000);
    lcd.clear();
    lcd.print(String(event.pressure *0.01450377) + " psi/" + String(event.pressure));
//    delay(2000);
//    lcd.clear();
//    lcd.print(event.pressure);
    lcd.setCursor(0,1);
    lcd.print("hectoPascals");
     delay(2000);
//    lcd.scrollDisplayLeft();
//    delay(7000);
    lcd.clear();
    delay(500);

//  create logic to write alerts dependent on range of readings
    if (event.pressure < 970) {
//      lcd.autoscroll();
      digitalWrite(ledStormy, HIGH);
      lcd.print("Stormy weather may be coming.");
      delay(1000);
      lcd.clear();
      delay(500);
    }
    else if (event.pressure >= 970 && event.pressure < 990) {
//      lcd.autoscroll();
      digitalWrite(ledRainy, HIGH);
      lcd.print("Rainy weather may be coming.");
      delay(1000);
      lcd.clear();
      delay(500);
    }
    else if (event.pressure >= 990 && event.pressure < 1010) {
//      lcd.autoscroll();
      digitalWrite(ledChange, HIGH);
      lcd.print("Change in");
      lcd.setCursor(0,1);
      lcd.print("weather ahead.");
      delay(3000);
      lcd.clear();
      delay(500);
    }
    else if (event.pressure >= 1010 && event.pressure < 1030) {
//      lcd.autoscroll();
      lcd.print("Fair weather ahead.");
      delay(1000);
      lcd.clear();
      delay(500);
    }
    else if (event.pressure >= 1030) {
//      lcd.autoscroll();
      lcd.print("Very dry weather ahead.");
      delay(1000);
      lcd.clear();
      delay(500);
    } else {
      lcd.print("Error");
    }
    
    /* Calculating altitude with reasonable accuracy requires pressure    *
     * sea level pressure for your position at the moment the data is     *
     * converted, as well as the ambient temperature in degress           *
     * celcius.  If you don't have these values, a 'generic' value of     *
     * 1013.25 hPa can be used (defined as SENSORS_PRESSURE_SEALEVELHPA   *
     * in sensors.h), but this isn't ideal and will give variable         *
     * results from one day to the next.                                  *
     *                                                                    *
     * You can usually find the current SLP value by looking at weather   *
     * websites or from environmental information centers near any major  *
     * airport.                                                           *
     *                                                                    *
     * For example, for Paris, France you can check the current mean      *
     * pressure and sea level at: http://bit.ly/16Au8ol                   */
     
    /* First we get the current temperature from the BMP085 */
    float temperature;
    bmp.getTemperature(&temperature);
    temperature = ((temperature * 9)/5) + 32;
    lcd.print("Temperature: ");
    lcd.setCursor(0,1);
    lcd.print(temperature);
    lcd.print(" F");
    delay(2000);
    lcd.clear();
    delay(500);

    /* Then convert the atmospheric pressure, and SLP to altitude         */
    /* Update this next line with the current SLP for better results      */
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    lcd.print("Altitude:"); 
    lcd.setCursor(0,1);
    lcd.print(bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure) /.3048); 
    lcd.print(" feet");
    delay(2000);
    lcd.clear();
  }
  else
  {
    lcd.print("Sensor error");
  }
  delay(1000);





  
  // put your main code here, to run repeatedly:


//  lcd.blink();
//  delay(4000);
//
//  lcd.noBlink();
//
//  lcd.cursor();
//  delay(2000);
//  lcd.noCursor();
//
//  lcd.clear();
}
