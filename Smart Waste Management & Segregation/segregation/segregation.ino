#define BLYNK_PRINT Serial1
#include <BlynkSimpleStream.h>

char auth[] = "3Dj06uWXos0uVHrwNZO2rzH9eKO0NdXW";

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

BLYNK_WRITE(V2) //Button Widget is writing to pin V1
{
  runButton = param.asInt(); 
}

BLYNK_READ(V3) {
  Blynk.virtualWrite(V3, wasteType);
}

void setup(){
  
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  Serial.println("Reading From the Sensor ...");
  Servo1.attach(servoPin); 
  
  Blynk.begin(Serial, auth);

  }

void loop(){
   output_value= analogRead(sensor_pin);

   output_value_per = map(output_value,893,0,0,100);

   Serial.print("Mositure : ");

   Serial.println(output_value);
   Serial.println(output_value_per);

   if(runButton){
    runMotor();
    }
      
    Servo1.write(90);
    Serial.println("%");

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
      wasteType = "WET";           
      delay(50);
      }
    }

    if(output_value_per = 0 )
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
