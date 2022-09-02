int mode = 0;//上位机用mode记录模式，0表示初始状态，1表示自由模式，2表示音游模式
int pause_flag = 0;//pause_flag表示是否暂停，0不暂停1暂停
//基本规则：发送大写字母表示将要获取信息，发送小写字母表示将要发送信息，大写Z表示信息发送/接受完毕，下位机可以退出读取状态

void Play(){
//感觉是已有的
}
void Detect(){
//已有
}

//主板从下位机1接收模式信号、暂停信号
void Serial1ReadMode(){
    Serial1.write('M');//发送模式接受标志给下位机1
    if(Serial1.available()){
        mode=Serial1.read();//从下位机1接收模式信号mode
    }

    Serial1.write('P');//发送暂停接受标志给下位机1
    if(Serial1.available()){
        pause_flag=Serial1.read();//从下位机1接收暂停信号mode
    }

    Serial1.write('Z');
}


//把模式和是否暂停发送到下位机2
void Serial2WriteMode(){
    Serial2.write('m');
    Serial2.write(mode);
    Serial2.write('p');
    Serial2.write(pause_flag);
    Serial2.write('Z');
}


void Serial1Write1(){
//好像不用了，屏幕所有操作在下位机上完成，这意味着模式选择是由下位机1传到主板
}


void Serial1WriteDrum(){
//给下位机1传送击打信号，把detect()到的信号传过去，数字1234表示4个，这个应该也是已有
}

void Serial2Write2(){
//应该是在上位机进行计分，然后传给下位机1在屏幕上进行显示
}

// void GetScoreFrom2(){
//     Serial2.write('G');//等待，发送标志G来获取,由于显示问题，只显示最后评级SABCD
//     if(Serial2.available()){
//         final_score=Serial2.read();
//     }
// }


