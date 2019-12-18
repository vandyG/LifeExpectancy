#define BLYNK_PRINT Serial1
#include <BlynkSimpleStream.h>

char auth[] = "3Dj06uWXos0uVHrwNZO2rzH9eKO0NdXW";

const int trigPin1 =  10;       //grey
const int echoPin1 = 9;         //purple

const int trigPin2 = 8;
const int echoPin2 = 11;

#define led1 13      //green
#define led2 7       //white
#define led3 12      //red

#define led4 49      //green 
#define led5 51      //white
#define led6 53      //red

float duration1, distance1, duration2, distance2;

BLYNK_READ(V0) {
  Blynk.virtualWrite(V0, (1-((distance1-3)/14))*100);
}

BLYNK_READ(V1) {
  Blynk.virtualWrite(V1, (1-((distance2-3)/14))*100);
}


void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);


  Blynk.begin(Serial, auth);
}
void loop()
{
  calDist(trigPin1, echoPin1, 1);
  calDist(trigPin2, echoPin2, 2);
  
  glow(led1, led2, led3, distance1);
  glow(led4, led5, led6, distance2);

  Blynk.run();
}

void glow(int l1, int l2, int l3, int distance)
{
  if(distance < 8)
  {
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(l3, HIGH);
  }
  else if(distance > 8 && distance < 12)
  {
    digitalWrite(l1, LOW);
    digitalWrite(l2, HIGH);
    digitalWrite(l3, LOW);
  }
  else if(distance > 12)
  {
    digitalWrite(l1, HIGH);
    digitalWrite(l2, LOW);
    digitalWrite(l3, LOW);
  } 
}

void calDist(int trigPin, int echoPin, int sensorNo)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  if(sensorNo == 2)
  {
    duration2 = pulseIn(echoPin, HIGH);
    distance2 = (duration2*.0343)/2;
    }
  else
  {
    duration1 = pulseIn(echoPin, HIGH);
    distance1 = (duration1*.0343)/2;
    }
  }
