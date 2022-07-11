#include<SoftwareSerial.h>
#include <UTFT.h>
#include <avr/pgmspace.h>
UTFT myGLCD(QD_TFT180A,A2,A1,A5,A4,A3);  // Remember to change the model parameter to suit your display module!
//SoftwareSerial mySerial(0,1);//RX,TX
extern unsigned int mysquare[0x400];
extern unsigned int white[0x38];
//extern unsigned int tux[0x1000];
extern unsigned int myfig[0x400];
extern unsigned int circle[0x240];
extern unsigned int line[0x100];
char a;
void setup()
{
   Serial.begin(9600);
//    myGLCD.InitLCD(PORTRAIT);myGLCD.fillScr(0, 0, 0);
  DDRD=0B11110000;  //  二进制顺序为D7--D0；1为输出，0为输入  
//  PORTD=0B00000000; //  二进制顺序为D7--D0；1为高电平，0为低电平 
}

void loop()
{
     
  if(Serial.available())
    {
   // myGLCD.fillScr(0, 0, 0); 
      a=Serial.read();
       Serial.println(a);
      switch (a){
        case '1':
          Serial.println("draw1");
           PORTD=0B11110000; //  二进制顺序为D7--D0；1为高电平，0为低电平 
           delay(100);
            PORTD=0B00000000; //  二进制顺序为D7--D0；1为高电平，0为低电平 
        //  digitalWrite(7, HIGH);   // 
        //  delay(100);
        //  digitalWrite(7, LOW);
          break;
        case '2':
          Serial.println("draw2");
          digitalWrite(6, HIGH);   // 
          delay(100);
          digitalWrite(6, LOW);
          break;
        case '3':
          Serial.println("draw3");
          digitalWrite(5, HIGH);   // 
          delay(100);
          digitalWrite(5, LOW);
          break;
        case '4':
          Serial.println("draw4");
          digitalWrite(4, HIGH);   // 
          delay(100);
          digitalWrite(4, LOW);
          break;
        default:
          Serial.println("default");
          break;
      
      }
            
     }   

}

