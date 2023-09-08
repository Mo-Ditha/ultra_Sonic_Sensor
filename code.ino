
#define BLYNK_TEMPLATE_ID "TMPL6-zRHQUAo"
#define BLYNK_TEMPLATE_NAME "UltraSonic"
#define BLYNK_AUTH_TOKEN "cnUCBEhcHJPzamNTyUbkXS4qLfDvtjbG"


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define  trig  D5
#define  echo  D4

long duration;
int distance;

// You should get Auth Token in the Blynk App.



// Your WiFi credentials.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Moditha";
char pass[] = "12345678";

BlynkTimer timer;
WidgetLCD lcd(V0);
void setup()
{
  // Debug console
  pinMode(trig, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echo, INPUT);   // Sets the echoPin as an Inpu
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
void sendSensor()
{
  digitalWrite(trig, LOW);   // Makes trigPin low
  delayMicroseconds(2);       // 2 micro second delay

  digitalWrite(trig, HIGH);  // tigPin high
  delayMicroseconds(10);      // trigPin high for 10 micro seconds
  digitalWrite(trig, LOW);   // trigPin low

  duration = pulseIn(echo, HIGH);   //Read echo pin, time in microseconds
  distance = duration * 0.034 / 2;   //Calculating actual/real distance

  Serial.print("Distance = ");        //Output distance on arduino serial monitor
  Serial.println(distance);

  Blynk.virtualWrite(V3, distance);
  
  lcd.print(0, 0, "voidloopRobotech"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(0, 1, "Distance: " + String(distance) + "cm  ");
  delay(1000); 

}
