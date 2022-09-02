// serial0 上位机
// serial2 放音乐的下位机
void setup()
{
    //略
}
void loop()
{
    if (mode == 0) // reset后的初始状态
    {   
        ReadKey();          //读取按键状态
        KeepListening();    //持续读取上位机信息，读到大写Z退出
        // Serial0Read0();     //读取上位机的信息
        // ChangeArguments0(); //根据读到的参数来改变参数(mode,还有屏幕要显示的内容)
        // Serial0Write0();    //给上位机发消息，确认模式已经改变
        //Write函数会在KeepListening()函数中被调用，逻辑是收到上位机的信号之后立刻返回对应的值
    }
    else if (mode == 1) //自由模式
    {
        Serial0Read1();
        ChangeArguments1(); //把敲击的情况随便可视化一下就行。
        //并且要考虑到上位机被按键改变状态之后传来的消息(switch case很多次就行)
    }
    else if (mode == 2)
    {
        Serial0Read1();     //注意要把mode从2到3的时候上位机发送来的信号也考虑进去。
        ChangeArguments1(); //把敲击的情况随便可视化一下就行。
        //并且要考虑到上位机被按键改变状态之后传来的消息(switch case很多次就行)
    }
    else if (mode == 3) //跟上位机一样，一次过
    {

        Serial0Read3();     //从上位机那读取分值。可以用while(!...)的办法等消息来。
        ChangeArguments3(); //对应的参数改改
    }
    Display(mode, contents); //可以输入两个参数，事先把各种特殊图形都封装好，放在不同mode对应的数组里。
    //又或者如模式0有1、2、3种情况，contents分别为1、2、3
    //问题：音乐对应的可视化界面怎么处理？
}
