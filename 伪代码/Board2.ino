// serial0 上位机
// serial1 led下位机
void setup()
{
    //略
}
void loop()
{
    if (mode == 0) // reset后的初始状态
    {
        Serial0Read0();     //读取上位机的信息
        ChangeArguments0(); //根据读到的参数来改变参数(mode,还有音乐要显示的内容)
        Serial0Write0();    //给上位机发消息，确认模式已经改变
    }
    //如果是自由模式的话，这个板子的mode不改变，还是0
    else if (mode == 2) //音游模式
    {
        Play();         //一次一个音符的放
        Serial0Read2(); //注意要把mode从2到3的时候上位机发送来的信号也考虑进去。
    }
    else if (mode == 3) //跟上位机一样，一次过
    {

        Count(); //计分

        Serial0Write3(); //告诉上位机总分
    }
}