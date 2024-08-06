#define BLYNK_TEMPLATE_ID "TMPL3329fwMU6"
#define BLYNK_TEMPLATE_NAME "Robotics"
#define BLYNK_AUTH_TOKEN "_dlxsGGHLmibR5TzwUZ_Tj5hvI-ZHoJC"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int Speed = 255;
int direc, forv, rightv, handmode;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "DJ";
char pass[] = "hotspot1234";

BLYNK_WRITE(V0)
{
  direc = param.asInt();
  Serial.println(direc);
}

BLYNK_WRITE(V3)
{
  handmode = param.asInt();
}

BLYNK_WRITE(V7)
{
  forv = param.asInt();
  Serial.println("Forward_voice");
}

BLYNK_WRITE(V8)
{
  rightv = param.asInt();
  Serial.println("Right_voice");
}

void voicecarcontrol()
{
  if (forv == 1)
  {
    Serial.println("Forward_voice");
    analogWrite(D0, Speed);
    analogWrite(D5, Speed);
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, LOW);
    delay(5000);
  }
  else if (rightv == 1)
  {
    Serial.println("Right_voice");
    analogWrite(D0, Speed);
    analogWrite(D5, Speed);
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    delay(5000);
  }
  else
  {
    Serial.println("Stop_voice");
    car_stop();
  }

  forv = 0;
  rightv = 0;
}

void handcarcontrol()
{
  if (direc == 1)
  {
    car_forward();
    Serial.println("hand_forward");
  }
  else if (direc == 2)
  {
    car_backward();
    Serial.println("hand_back");
  }
  else if (direc == 4)
  {
    car_left();
    Serial.println("hand_left");
  }
  else if (direc == 3)
  {
    car_right();
    Serial.println("hand_right");
  }
  else
  {
    car_stop();
    Serial.println("hand_stop");
  }
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT); // left in1
  pinMode(D2, OUTPUT); // left in2
  pinMode(D3, OUTPUT); // right in1
  pinMode(D4, OUTPUT); // right in2
  pinMode(D5, OUTPUT);
}

void loop()
{
  Blynk.run();
  if (handmode == 0){
    handcarcontrol();
  }
  else{
    voicecarcontrol();
  }
}

void car_forward()
{
  analogWrite(D0, Speed);
  analogWrite(D5, Speed);
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
}

void car_backward()
{
  analogWrite(D0, Speed);
  analogWrite(D5, Speed);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
}
