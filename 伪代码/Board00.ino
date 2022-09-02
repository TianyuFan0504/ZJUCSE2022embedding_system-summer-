#include <SoftwareSerial.h>
//没有接线的传感器对应的口的检测函数要在main里注释掉，否则因为这些口的电平是不确定的，会随机触发。
//七个压电片
#define Piezo1Pin A1
#define Piezo2Pin A2
#define Piezo3Pin A3
#define Piezo4Pin A4
#define Piezo5Pin A5
#define Piezo6Pin A6
#define Piezo7Pin A7
//音调对应的midi参数
#define C5 60 // C5
#define D5 62
#define E5 64
#define G5 67
#define A5 69

// Photo1
int Photo1Pin = 2;
int CurrPhoto1Val = 0;
int PrevPhoto1Val = 0;
// Photo2
int Photo2Pin = 3;
int CurrPhoto2Val = 0;
int PrevPhoto2Val = 0;

// Piezo1
int Piezo1Cutoff = 300; //截止频率
int Piezo1Vel = 0;
int CurrPiezo1Val = 0;
int PrevPiezo1Val = 0;
// Piezo2
int Piezo2Cutoff = 300;
int Piezo2Vel = 0;
int CurrPiezo2Val = 0;
int PrevPiezo2Val = 0;

// Piezo3
int Piezo3Cutoff = 300;
int Piezo3Vel = 0;
int CurrPiezo3Val = 0;
int PrevPiezo3Val = 0;
// Piezo4
int Piezo4Cutoff = 300;
int Piezo4Vel = 0;
int CurrPiezo4Val = 0;
int PrevPiezo4Val = 0;

// Piezo5
int Piezo5Cutoff = 300;
int Piezo5Vel = 0;
int CurrPiezo5Val = 0;
int PrevPiezo5Val = 0;
// Piezo6
int Piezo6Cutoff = 300;
int Piezo6Vel = 0;
int CurrPiezo6Val = 0;
int PrevPiezo6Val = 0;
// Piezo7
int Piezo7Cutoff = 300;
int Piezo7Vel = 0;
int CurrPiezo7Val = 0;
int PrevPiezo7Val = 0;
// serial1 led下位机
// serial2 放音乐的下位机
int mode = 0;
void setup()
{
    Serial.begin(115200); // to computer
    Serial1.begin(9600);  // to led
    Serial2.begin(9600);  // to music
}
void loop()
{
    if (mode == 0) // reset后的初始状态
    {
        ReadKey();          //读取按键状态
        CompareKey();       //模式比较
        ChangeArguments0(); //改变对应参数
        Serial1Write0();    //①根据上方改变的参数去给其他板子发信息,例如音游模式就要下面准备蜂鸣器
        //②在按键选择的时候屏幕是要对应着改变的，屏幕显示什么也是由主机把当前的模式状态传给下位机，下位机据此显示对应内容
        Serial1Read0(); //看看下位机有没有发消息给上位机，有的话再做调整。
    }
    else if (mode == 1) //自由模式
    {
        DetectAndPlay();

        delay(3); //需要

        KeyDetect1(); //如果在进行演奏的过程中按下某些按键，可以起到暂停、回到主界面（mode=0）、静音某些乐器的作用..
        //..如果有必要跟下位机说一声（如模式改变）那也可以加一个
        Serial1Read1(); //看看下位机有没有发消息给上位机，有的话再做调整。
        //如果在实践中证明这个会很影响演奏响应速度，则可以改成把上下位机连几根IO线，读其IO值。
    }
    else if (mode == 2) //音游模式
    //注意，上位机和下位机的时钟是不需要同步的（？），当SerialWrite2发送信号过去的时候，由下位机来判断这是不是踩在节奏上了。
    {
        //对其中一个传感器
        DetectAndPlay(); //上位机与传感器,播放,传信号

        KeyDetect2(); //如果在进行演奏的过程中按下某些按键，可以起到暂停、回到主界面（mode=0）、静音某些乐器的作用..
        //..如果有必要跟下位机说一声（如模式改变）那也可以加一个
        Serial1Read2(); //看看下位机有没有发消息给上位机，有的话再做调整。例如一首歌放完了，那mode应该变成3了，结束演奏。
        Serial2Read2(); // mode3?
        //记得把mode改变的事传回给其他下位机
        //如果在实践中证明这个会很影响演奏响应速度，则可以改成把上下位机连几根IO线，读其IO值。
    }
    else if (mode == 3) //演奏结束。这串代码在一首歌放完之后只跑一遍，跑完之后回到mode0，所以可以随便加delay
    {
        Serial1Write3(); //告诉led改变模式了。
        Serial2Write3(); //告诉放音乐的可以结束计分了
        delay();
        Serial2Read3(); //从放音乐的板子读取分数
        delay();
        Serial1Write3();    //把这个分值传给led板子
        ChangeArguments3(); // mode=0，以及其他。
    }
    //一个欠考虑的环节可能是当从一个mode忽然转成另一个的时候要做的操作。
    // 0->1;1->0;0->2;2->0;2->3,3->0六种情况。
    //另外在加delay的地方要慎重。
}
void DetectAndPlay(void)
{ // Photo1
    CurrPhoto1Val = digitalRead(Photo1Pin);
    if (CurrPhoto1Val == 1 && PrevPhoto1Val == 0) //上升沿
    {
        playMidiNote(1, C5, 127);
        Serial1.println(1);
        if (mode == 2)
            Serial2.println(1);
    }
    PrevPhoto1Val = CurrPhoto1Val;

    // Photo2
    CurrPhoto2Val = digitalRead(Photo2Pin);
    if (CurrPhoto2Val == 1 && PrevPhoto2Val == 0)
    {
        playMidiNote(2, C5, 127);
        Serial1.println(2);
        if (mode == 2)
            Serial2.println(2);
    }
    PrevPhoto2Val = CurrPhoto2Val;

    // Piezo1
    CurrPiezo1Val = analogRead(Piezo1Pin);
    if (CurrPiezo1Val > Piezo1Cutoff && PrevPiezo1Val < Piezo1Cutoff)
    {
        if (CurrPiezo1Val > 750)
            CurrPiezo1Val = 750;
        Piezo1Vel = 80 + (CurrPiezo1Val - Piezo1Cutoff) / 5;
        if (Piezo1Vel > 127)
            Piezo1Vel = 127;
        playMidiNote(3, C5, Piezo1Vel);
        Serial1.println(3);
        if (mode == 2)
            Serial2.println(3);
    }
    PrevPiezo1Val = CurrPiezo1Val;
    // Piezo2
    CurrPiezo2Val = analogRead(Piezo2Pin); // Connect the sensor to analog pin 0
    if (CurrPiezo2Val > Piezo2Cutoff && PrevPiezo2Val < Piezo2Cutoff)
    {
        if (CurrPiezo2Val > 750)
            CurrPiezo2Val = 750;
        Piezo2Vel = 80 + (CurrPiezo2Val - Piezo2Cutoff) / 5;
        if (Piezo2Vel > 127)
            Piezo2Vel = 127;
        playMidiNote(4, C5, Piezo2Vel);
        Serial1.println(4);
        if (mode == 2)
            Serial2.println(4);
    }
    PrevPiezo2Val = CurrPiezo2Val;
    // Piezo3
    CurrPiezo3Val = analogRead(Piezo3Pin);
    if (CurrPiezo3Val > Piezo3Cutoff && PrevPiezo3Val < Piezo3Cutoff)
    {
        if (CurrPiezo3Val > 750)
            CurrPiezo3Val = 750;
        Piezo3Vel = 80 + (CurrPiezo3Val - Piezo3Cutoff) / 5;
        if (Piezo3Vel > 127)
            Piezo3Vel = 127;
        playMidiNote(5, C5, Piezo3Vel);
        Serial1.println(5);
        if (mode == 2)
            Serial2.println(5);
    }
    PrevPiezo3Val = CurrPiezo3Val;

    // Piezo4
    CurrPiezo4Val = analogRead(Piezo4Pin);
    if (CurrPiezo4Val > Piezo4Cutoff && PrevPiezo4Val < Piezo4Cutoff)
    {
        if (CurrPiezo4Val > 750)
            CurrPiezo4Val = 750;
        Piezo4Vel = 80 + (CurrPiezo4Val - Piezo4Cutoff) / 5;
        if (Piezo4Vel > 127)
            Piezo4Vel = 127;
        playMidiNote(5, D5, Piezo4Vel);
        Serial1.println(6);
        if (mode == 2)
            Serial2.println(6);
    }
    PrevPiezo4Val = CurrPiezo4Val;
    // Piezo5
    CurrPiezo5Val = analogRead(Piezo5Pin); // Connect the sensor to analog pin 0
    if (CurrPiezo5Val > Piezo5Cutoff && PrevPiezo5Val < Piezo5Cutoff)
    {
        if (CurrPiezo5Val > 750)
            CurrPiezo5Val = 750;
        Piezo5Vel = 80 + (CurrPiezo5Val - Piezo5Cutoff) / 5;
        if (Piezo5Vel > 127)
            Piezo5Vel = 127;
        playMidiNote(5, E5, Piezo5Vel);
        Serial1.println(7);
        if (mode == 2)
            Serial2.println(7);
    }
    PrevPiezo5Val = CurrPiezo5Val;
    // Piezo6
    CurrPiezo6Val = analogRead(Piezo6Pin); // Connect the sensor to analog pin 0
    if (CurrPiezo6Val > Piezo6Cutoff && PrevPiezo6Val < Piezo6Cutoff)
    {
        if (CurrPiezo6Val > 750)
            CurrPiezo6Val = 750;
        Piezo6Vel = 80 + (CurrPiezo6Val - Piezo6Cutoff) / 5;
        if (Piezo6Vel > 127)
            Piezo6Vel = 127;
        playMidiNote(5, G5, Piezo6Vel);
        Serial1.println(8);
        if (mode == 2)
            Serial2.println(8);
    }
    PrevPiezo6Val = CurrPiezo6Val;
    // Piezo7
    CurrPiezo7Val = analogRead(Piezo7Pin); // Connect the sensor to analog pin 0
    if (CurrPiezo7Val > Piezo7Cutoff && PrevPiezo7Val < Piezo7Cutoff)
    {
        if (CurrPiezo7Val > 750)
            CurrPiezo7Val = 750;
        Piezo7Vel = 80 + (CurrPiezo7Val - Piezo7Cutoff) / 5;
        if (Piezo7Vel > 127)
            Piezo7Vel = 127;
        playMidiNote(5, A5, Piezo7Vel);
        Serial1.println(9);
        if (mode == 2)
            Serial2.println(9);
    }
    PrevPiezo7Val = CurrPiezo7Val;
}
void playMidiNote(byte channel, byte note, byte velocity)
{
    byte midiMessage = 0x90 + (channel - 1);
    Serial.write(midiMessage);
    Serial.write(note);
    Serial.write(velocity);
}
