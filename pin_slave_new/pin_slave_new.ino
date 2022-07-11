#include<SoftwareSerial.h>
#include <UTFT.h>
#include <avr/pgmspace.h>



//曲子的节拍，即音符持续时间
float duration[] =
{
  1, 1, 0.5, 0.5, 1,
  0.5, 0.5, 0.5, 0.5, 1, 0.5, 0.5,
  0.5, 1, 0.5, 1, 0.5, 0.5,
  0.5, 0.5, 0.5, 0.5, 1, 1,

  1, 1, 1 + 1,
  0.5, 1, 1 + 0.5, 1,
  1, 1, 0.5, 0.5, 1,
  0.5, 1, 1 + 0.5, 1,
  0.5, 0.5, 0.5, 0.5, 1 + 1,
  0.5, 1, 1 + 0.5, 1,
  1 + 1, 0.5, 0.5, 1,
  1 + 1 + 1 + 1,
  0.5, 0.5, 0.5 + 0.25, 0.25, 0.5 + 0.25, 0.25, 0.5 + 0.25, 0.25,
  0.5, 1, 0.5, 1, 1,
  0.5, 0.5, 0.5 + 0.25, 0.25, 0.5 + 0.25, 0.25, 0.5 + 0.25, 0.25,
  0.5, 1, 0.5, 1, 1,
  1 + 1, 0.5, 0.5, 1,
  1 + 1 + 1 + 1,
  0.5, 1, 0.5, 1 + 1,
  0.5, 1, 0.5, 1 + 1,
  1 + 1, 0.5, 0.5, 1,
  1 + 1 + 1 + 1
};

int length;//定义一个变量用来表示共有多少个音符
char a;
int begin_time;
void check_a(char a){
      switch (a){
        case '1':
          Serial.println("draw1");
          digitalWrite(7, HIGH);   // 
          delay(50);
          digitalWrite(7, LOW);
          break;
        case '2':
          Serial.println("draw2");
          digitalWrite(6, HIGH);   // 
          delay(50);
          digitalWrite(6, LOW);
          break;
        case '3':
          Serial.println("draw3");
          digitalWrite(5, HIGH);   // 
          delay(50);
          digitalWrite(5, LOW);
          break;
        case '4':
            Serial.println("draw4");
            digitalWrite(4, HIGH);   // 
            delay(50);
            digitalWrite(4, LOW);
            break;
        default:
          Serial.println("default");
          delay(50);
          break;
      }
}
void setup()
{
   Serial.begin(9600);

  DDRD=0B11110000;  //  二进制顺序为D7--D0；1为输出，0为输入  
//  PORTD=0B00000000; //  二进制顺序为D7--D0；1为高电平，0为低电平 
  length = sizeof(duration) / sizeof(duration[0]); //这里用了一个sizeof函数，查出数组里有多少个音符
}

void loop()
{
  if(a!='s'){
    if(Serial.available()){a=Serial.read();Serial.println(a);}
  
  }
 //   else{Serial.println("waiting...");}
    if(a=='s'){
          begin_time=millis();
          Serial.println(begin_time);
          while(1){
              if(Serial.available()){a=Serial.read();Serial.println(a);check_a(a);}
          }
    }
    

}

