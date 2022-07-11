#include<SoftwareSerial.h>

void setup()
{
   Serial1.begin(9600);
   Serial.begin(9600);

}

void loop()
{
    for(int i=0;i<=100;i++) {
        Serial1.print(i%2);
        Serial.print(i%2);
   delay(1000);}  
}

