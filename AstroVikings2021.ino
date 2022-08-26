//---------------------------------------------------------------------------------------------//Objects------------------------------------------------------------------------------ 

//Servo--------------------------------------------------------------------------------
#include <Servo.h>
Servo FlapServo;
//Altimeter----------------------------------------------------------------------------
#include <Wire.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp; // I2C 
//Accelerometer------------------------------------------------------------------------ 

//---------------------------------------------------------------------------------------------//Constants----------------------------------------------------------------------------
double height = 243.84;//height intending to reach , 243.84m
//int StartDeg = 0; 
//int EndDeg = 180;  
double Pressure = 1013.25 ; //Default 1013.25; hPa pressure at sea level for location and day (hectopascal)
int i=0;
double ReadSpeed = 2000;
int pos=0; 
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() 
{ 
//Servo
FlapServo.attach(11); 
//Altimeter 

 Serial.begin(9600);
  Serial.println(F("BMP280 test"));

  //if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    while (1) delay(10);
  } 
  

bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */  
//Accelerometer 

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() 
{  

 if(bmp.readAltitude(Pressure)>=height){
FlapServo.write(180); 
 } 
 else{ 
  FlapServo.write(0);
 }
   
 
Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

Serial.print(F("Temperature = "));
  Serial.print((bmp.readTemperature())*(1.8)+(32));
  Serial.println(" *F");

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(Pressure)); /* Adjusted to local forecast!; defualt is 1013.25 */ 
  
  Serial.println(" m");

  Serial.println();
  delay(ReadSpeed); 

 



 
}
