//hello
int key_up = 2;
int key_down = 3;
int key_choose = 4;
int key_pause = 5;
int led_pin = 9;
void setup() {
 pinMode(led_pin,OUTPUT);//这个是led的IO口
 pinMode(key_up,INPUT);//这个是按键控制的IO口
 pinMode(key_down,INPUT);//这个是按键控制的IO口
 pinMode(key_choose,INPUT);//这个是按键控制的IO口
 pinMode(key_pause,INPUT);//这个是按键控制的IO口
Serial.begin(9600);//把是否按下的信息通过串口来进行显示出来；
}
int flag = 0;//这个是判断按键是否按下的一个标志变量；
void loop() {
 // digitalWrite(key_pin,LOW);
 // delay(10);
  //flag = ;
 if(digitalRead(key_up) == LOW)
  {
    flag &= 126;
    digitalWrite(led_pin,LOW);
  //Serial.println("按键没有按下");
  }
 else
 {
  flag |= 1;
  digitalWrite(led_pin,HIGH);
  //Serial.println("按键有按下");
 }
 if(digitalRead(key_down) == LOW)
  {
    flag &= 125;
    digitalWrite(led_pin,LOW);
  }
 else
 {
  flag |= 2;
  digitalWrite(led_pin,HIGH);
 }
 if(digitalRead(key_choose) == LOW)
  {
    flag &= 123;
  }
 else
 {
  flag |= 4;
 }
 if(digitalRead(key_pause) == LOW)
  {
    flag &= 119;
  }
 else
 {
  flag |= 8;
 }
 Serial.print("flag=");
 Serial.println(flag);
}
