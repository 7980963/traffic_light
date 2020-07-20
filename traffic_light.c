#include "LedControl.h"
//定义向南红绿灯针脚
int south_red = 8;
int south_yellow = 9;
int south_green = 10;
//通过时间变化
int num_time = 1;
int num_stop = 0;
//定义向北红绿灯针脚
int north_red = 5;
int north_yellow = 6;
int north_green = 7;
//定义调整通过时间按钮针脚
int time_button=4;
//定义急停按钮针脚
int stop_button=3;
//定义蜂鸣器针脚
int buzzer=2;
//定义8×8点阵针脚
int CLK = 11;
int CS = 12;
int DIN = 13;
LedControl lc=LedControl(DIN,CLK,CS,1);
//向北指示箭头点阵屏样式
byte north[8]={
B00010000,
B00110000,
B01110000,
B11111111,
B11111111,
B01110000,
B00110000,
B00010000,};
//向南指示箭头点阵屏样式
byte south[8]={
B00001000,
B00001100,
B00001110,
B11111111,
B11111111,
B00001110,
B00001100,
B00001000,};
//倒计时3点阵屏样式
byte L_3[8]={
B00000000,
B01000010,
B11010011,
B11011011,
B11011011,
B01111110,
B00110100,
B00000000,};
//倒计时2点阵屏样式
byte L_2[8]={
B10000100,
B11000110,
B11000011,
B11100011,
B11110011,
B11011110,
B11001100,
B10000000,};
//倒计时1点阵屏样式
byte L_1[8]={
B00000000,
B10000100,
B10000110,
B11111111,
B11111111,
B10000000,
B10000000,
B00000000,};
//紧急停止点阵屏样式
byte stop[8]={
B10000001,
B01000010,
B00100100,
B00011000,
B00011000,
B00100100,
B01000010,
B10000001,};
//黑屏点阵屏样式
byte black[8]={
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,};
void setup(){
    //设置南向红绿灯针脚模式为输出
    pinMode(south_red, OUTPUT);
    pinMode(south_yellow, OUTPUT);
    pinMode(south_green, OUTPUT);
    //设置北向红绿灯针脚模式为输出
    pinMode(north_red, OUTPUT);
    pinMode(north_yellow, OUTPUT);
    pinMode(north_green, OUTPUT);
    //设置调整通过时间按钮针脚模式为输入
    pinMode(time_button, INPUT);
    //设置急停按钮针脚模式为输入
    pinMode(stop_button, INPUT);
    //设置蜂鸣器针脚模式为输出
    pinMode(buzzer, OUTPUT);
}
void loop(){
   int val_time=digitalRead(time_button);
   //if判断按键是否按下
   if(val_time==0)
   {
     delay(50);
     if(val_time==0)
     {
        num_time++;
       //wihile判断当按键被按住时暂停程序
       while(digitalRead(time_button)==0)
        {
         delay(50);
        }
     }
   } 
      if(num_time==1)
      {
      //红绿灯10S切换方向
      go_10s();
      }
      if(num_time==2)
      {
      //红绿灯10S切换方向
      go_15s();
      }
      if(num_time==3)
      {
      //红绿灯10S切换方向
      go_20s();
      }
      if(num_time==4)
      {
      //红绿灯10S切换方向
      go_10s();
      //返回10S切换方向状态
      num_time=1;
      }
      if(num_time==5)
      {
      //不进行任何操作
      }
}
//当向南为绿灯时各信号灯状态
void south_go(){
    LED_south();
    digitalWrite(north_red, HIGH);
    digitalWrite(south_red, LOW);    
    digitalWrite(south_green, HIGH);
    digitalWrite(north_green, LOW);
    digitalWrite(south_yellow, LOW);
    digitalWrite(north_yellow, LOW);
}
//当向北为绿灯时各信号灯状态
void north_go(){
    LED_north();
    digitalWrite(north_red, LOW);
    digitalWrite(south_red, HIGH);    
    digitalWrite(south_green, LOW);
    digitalWrite(north_green, HIGH);
    digitalWrite(south_yellow, LOW);
    digitalWrite(north_yellow, LOW);
}
//黄灯闪烁三秒+倒计时
void yellow_flush(){
    LED_3();
    digitalWrite(south_yellow, HIGH);
    digitalWrite(north_yellow, HIGH);
    flag_test();
    delay(500);
    digitalWrite(south_yellow, LOW);
    digitalWrite(north_yellow, LOW);
    flag_test();
    delay(500);
    LED_2();
    digitalWrite(south_yellow, HIGH);
    digitalWrite(north_yellow, HIGH);
    flag_test();
    delay(500);
    digitalWrite(south_yellow, LOW);
    digitalWrite(north_yellow, LOW);
    flag_test();
    delay(500);
    LED_1();
    digitalWrite(south_yellow, HIGH);
    digitalWrite(north_yellow, HIGH);
    flag_test();
    delay(500);
    digitalWrite(south_yellow, LOW);
    digitalWrite(north_yellow, LOW);
    flag_test();
    delay(500);
}
//向北指示箭头显示函数
void LED_north(){
    lc.shutdown(0,false);
    lc.setIntensity(0,3);
    lc.clearDisplay(0);
    for (int row=0;row<8;row++)
    lc.setRow(0,row,north[row]);
}
//向南指示箭头显示函数
void LED_south(){
    lc.shutdown(0,false);
    lc.setIntensity(0,3);
    lc.clearDisplay(0);
    for (int row=0;row<8;row++)
    lc.setRow(0,row,south[row]);
}
//倒计时3显示函数
void LED_3(){
    lc.shutdown(0,false);
    lc.setIntensity(0,3);
    lc.clearDisplay(0);
    for (int row=0;row<8;row++)
    lc.setRow(0,row,L_3[row]);
}
//倒计时2显示函数
void LED_2(){
    lc.shutdown(0,false);
    lc.setIntensity(0,3);
    lc.clearDisplay(0);
    for (int row=0;row<8;row++)
    lc.setRow(0,row,L_2[row]);
}
//倒计时1显示函数
void LED_1(){
    lc.shutdown(0,false);
    lc.setIntensity(0,3);
    lc.clearDisplay(0);
    for (int row=0;row<8;row++)
    lc.setRow(0,row,L_1[row]);
}
//紧急停止显示函数
void LED_stop(){
    lc.shutdown(0,false);
    lc.setIntensity(0,3);
    lc.clearDisplay(0);
    for (int row=0;row<8;row++)
    lc.setRow(0,row,stop[row]);
}
//黑屏显示函数
void LED_black(){
    lc.shutdown(0,false);
    lc.setIntensity(0,3);
    lc.clearDisplay(0);
    for (int row=0;row<8;row++)
    lc.setRow(0,row,black[row]);
}
//红绿灯10S切换方向
void go_10s (){
    int delay_time;
    south_go();
    for(delay_time=0;delay_time<=7;delay_time++)
    {
      LED_south();
      flag_test();
      delay(1000);
    }
    yellow_flush();
    north_go();
    for(delay_time=0;delay_time<=7;delay_time++)
    {
      LED_north();
      flag_test();
      delay(1000);
    }
    yellow_flush();
}
//红绿灯15S切换方向
void go_15s (){
    int delay_time;
    south_go();
    yellow_flush();
   for(delay_time=0;delay_time<=12;delay_time++)
    {
      LED_south();
      flag_test();
      delay(1000);
    }
 north_go();
    for(delay_time=0;delay_time<=12;delay_time++)
    {
      LED_north();
      flag_test();
      delay(1000);
    }
    yellow_flush();
}
//红绿灯20S切换方向
void go_20s (){
    int delay_time;
    south_go();
    for(delay_time=0;delay_time<=17;delay_time++)
    {
      LED_south();
      flag_test();
      delay(1000);
    }
    yellow_flush();
    north_go();
    for(delay_time=0;delay_time<=17;delay_time++)
    {
      LED_north();
      flag_test();
      delay(1000);
    }
    yellow_flush();
}
//紧急停止状态
void all_stop(){
      num_stop=1;
      digitalWrite(north_red, HIGH);
      digitalWrite(south_red, HIGH);    
      digitalWrite(south_green, LOW);
      digitalWrite(north_green, LOW);
      digitalWrite(south_yellow, LOW);
      digitalWrite(north_yellow, LOW);      
      digitalWrite(buzzer, HIGH); 
      LED_stop();      
      delay(500);
      digitalWrite(buzzer, LOW); 
      LED_black();
      delay(500);
}
void flag_test(){
   int val_stop=digitalRead(stop_button);
   //if判断按键是否按下
   if(val_stop==0)
   {
     delay(50);
     if(val_stop==0)
     {
        num_stop++;
        //wihile判断当按键被按住时暂停程序
        while(digitalRead(stop_button)==0)
        {
         delay(50);
        }
     }
   } 
      if(num_stop==0)
      {
      //不进行任何操作
      }
      if(num_stop==1)
      {
      //使交通灯控制模块不进行任何操作
      num_time=5;
      //设置为紧急停止状态
      all_stop();
      }
      if(num_stop>=2)
      {
      //关闭紧急停止状态
      num_stop=0;
      //设置为10S模式
      num_time=1;
      }
  }
