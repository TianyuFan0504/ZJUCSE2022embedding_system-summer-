#include <SoftwareSerial.h>
// Piezo压电片，Photo光电
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
// key
int key_up = 8;
int key_down = 9;
int key_choose = 10;
int key_pause = 11;

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

int flag = 1;
int state = 1;
void setup()
{
    Serial.begin(115200);       //与电脑
    Serial1.begin(9600);        //与下位机1
    Serial2.begin(9600);        //与下位机2
    pinMode(key_up, INPUT);     //这个是按键控制的IO口
    pinMode(key_down, INPUT);   //这个是按键控制的IO口
    pinMode(key_choose, INPUT); //这个是按键控制的IO口
    pinMode(key_pause, INPUT);  //这个是按键控制的IO口
}
void loop()
{

    if (!state)
    {
        if (digitalRead(key_up) == LOW)
        {
            flag &= 126;
        }
        else
        {
            flag |= 1;
        }
        if (digitalRead(key_down) == LOW)
        {
            flag &= 125;
        }
        else
        {
            flag |= 2;
        }
        if (digitalRead(key_choose) == LOW)
        {
            flag &= 123;
        }
        else
        {
            flag |= 4;
        }
        if (digitalRead(key_pause) == LOW)
        {
            flag &= 119;
        }
        else
        {
            flag |= 8;
        }
        Serial2.print("flag=");
        Serial2.println(flag);
        delay(100);
        if (flag == 8)
        {
            Serial1.println('s');
            Serial2.println('s');
            state = 1;
        }
    }

    else
    {
        // Photo1
        CurrPhoto1Val = digitalRead(Photo1Pin);
        if (CurrPhoto1Val == 1 && PrevPhoto1Val == 0) //上升沿
        {
            playMidiNote(1, C5, 127);
            Serial1.println(1);
        }
        PrevPhoto1Val = CurrPhoto1Val;

        // Photo2
        CurrPhoto2Val = digitalRead(Photo2Pin);
        if (CurrPhoto2Val == 1 && PrevPhoto2Val == 0)
        {
            playMidiNote(2, C5, 127);
            Serial1.println(2);
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
            //  Serial1.println(3);
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
        }
        PrevPiezo7Val = CurrPiezo7Val;
        delay(3); //需要
    }
    // Serial1.println(1);
}

void playMidiNote(byte channel, byte note, byte velocity)
{
    byte midiMessage = 0x90 + (channel - 1);
    Serial.write(midiMessage);
    Serial.write(note);
    Serial.write(velocity);
}
