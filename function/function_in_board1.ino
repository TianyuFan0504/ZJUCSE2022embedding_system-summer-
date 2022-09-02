//这块是连接屏幕、按键的arduino板子

// 在宏定义中加入以下内容：
    // int key_up = 10;
    // int key_down = 11;
    // int key_choose = 12;
    // int key_pause = 13;
    // int state_flag = 1;//用state来控制状态,0表示音游模式，1表示自由模式
    // int start_flag = 0;//0表示仍在开始界面，1表示进入游戏模式
    // int pause_flag = 0;//1表示暂停
//在setup中加入以下内容:
    // pinMode(key_up, INPUT);     //这个是按键控制的IO口
    // pinMode(key_down, INPUT);   //这个是按键控制的IO口
    // pinMode(key_choose, INPUT); //这个是按键控制的IO口
    // pinMode(key_pause, INPUT);  //这个是按键控制的IO口

//读取按键状态，假设按键接在arduinoUNO板子上的10-13口子
void ReadKey(){

    if (digitalRead(key_up) == HIGH)
    {
        delay(30);
        if (digitalRead(key_up) == HIGH){
            state_flag = 1 - state_flag;
            // Serial1.println('u');Serial.println('u');//up
        }
    }

    if (digitalRead(key_down) == HIGH)
    {
        delay(30);
        if (digitalRead(key_down) == HIGH){
            state_flag = 1 - state_flag;
            // Serial1.println('d');Serial.println('d');//down
        }
    }

    if (digitalRead(key_choose) == HIGH)
    {
        delay(30);
        if (digitalRead(key_choose) == HIGH){
            start_flag = 1;
            // Serial1.println('c');Serial.println('c');//choose
        }
        
    }

    if (digitalRead(key_pause) == HIGH)
    {
        delay(30);
        if (digitalRead(key_pause) == HIGH){
            pause_flag = 1 - pause_flag;
            // Serial1.println('p');Serial.println('p');//pause
        }
    }
}


//char hear;
void KeepListening(){
    while(1){
        if(Serial1.available()){
            hear = Serial1.read();//从上位机接收
            switch hear:
                case 1:break;
                case 2:break;
                case 3:break;
                case 4:break;

                case 'M':
                    Serial1.write(mode);
                    break;
                case 'P':
                    Serial1.write(pause_flag)
                    break;

                case 'm':
                    mode = Serial1.read();
                    break;
                case 'p':
                    pause_flag = Serial1.read();
                    break;
                
                default:
                    break;

        }

        if(hear=='Z'){break;}


    }
    
}

