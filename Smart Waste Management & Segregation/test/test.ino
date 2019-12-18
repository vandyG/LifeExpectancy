/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  =>
  =>          USB HOWTO: http://tiny.cc/BlynkUSB
  =>

  This example shows how to send requested values to the Blynk App

  Project setup in the app:
    Value Display widget attached to V5. Set any reading
    frequency (i.e. 1 second)
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT SwSerial


#include <SoftwareSerial.h>
SoftwareSerial SwSerial(10, 11); // RX, TX
    
#include <BlynkSimpleStream.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "EnWK3Fraj0pSSRmou5dwlVOMsCDpajER";

int sensor_pin = A0;
int led_pin =13;

#include <Servo.h> 
int output_value ;
int output_value_per ;
int servoAngle;
int servoPin = 3; 
int runButton;
const char* wasteType;
Servo Servo1;

// This function is called when there is a Widget
// which is requesting data from Virtual Pin (5)
BLYNK_READ(V1)
{
  // This command writes Arduino's uptime in seconds to Virtual Pin (5)
   Blynk.virtualWrite(V1, wasteType);
}

BLYNK_WRITE(V0) //Button Widget is writing to pin V1
{
  runButton = param.asInt(); 
}

void setup()
{
  // Debug console
  SwSerial.begin(9600);
  Serial.begin(9600);
  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch

  pinMode(led_pin, OUTPUT);
  Servo1.attach(servoPin);
  
  Blynk.begin(Serial, auth);

  
}

void loop()
{
  output_value= analogRead(sensor_pin);

  output_value_per = map(output_value,893,0,0,100);

  if(runButton == 1){
    runMotor();
    }
      
    Servo1.write(90);
    
  Blynk.run();
}

void runMotor()
  {
    if(output_value_per > 0)
   {
    for(servoAngle = 90; servoAngle < 180; servoAngle++)
    {
      Servo1.write(servoAngle);   
      digitalWrite(led_pin, HIGH);
      wasteType = "WETX";           
      delay(50);
      }
    }

    else //if(output_value_per < 0 )
    {
      for(servoAngle = 90; servoAngle > 0; servoAngle--)
      {
        Servo1.write(servoAngle);    
        digitalWrite(led_pin, LOW); 
        wasteType = "DRY";     
        delay(50);    
        }
      }
    }
