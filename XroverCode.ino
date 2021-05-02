

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <SoftwareSerial.h>    

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define LOGO16_GLCD_HEIGHT 16 //定义显示高度
#define LOGO16_GLCD_WIDTH  16 //定义显示宽度

//中文：中  (存储点阵变量，用函数display.drawBitmap()调用即可)
static const unsigned char PROGMEM str_1[] =
{ 
0x00,0x00,0x0F,0x08,0x08,0x08,0x08,0xFF,0x08,0x08,0x08,0x08,0x0F,0x00,0x00,0x00,
0x00,0x00,0xF0,0x20,0x20,0x20,0x20,0xFF,0x20,0x20,0x20,0x20,0xF0,0x00,0x00,0x00
};

//中文：国
static const unsigned char PROGMEM str_2[] =
{ 
0x00,0x7F,0x40,0x48,0x49,0x49,0x49,0x4F,0x49,0x49,0x49,0x48,0x40,0x7F,0x00,0x00,
0x00,0xFF,0x02,0x12,0x12,0x12,0x12,0xF2,0x12,0x52,0x32,0x12,0x02,0xFF,0x00,0x00
};

#if (SSD1306_LCDHEIGHT != 64)
#endif


SoftwareSerial BT(10, 11);           //设置蓝牙与板子的连接端口。  pin 8  接蓝牙的 TXD    pin 9 接蓝牙的 RXD
//定义一个变量存数据。

const int motorPin1  = 9; // Pin  7 of L293
const int motorPin2  = 3;  // Pin  2 of L293
const int motorPin3  = 6; // Pin  7 of L293
const int motorPin4  = 5;  // Pin  2 of L293



void setup()
{
  Serial.begin(9600);              //串口监视器通信速率，38400

   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  display.clearDisplay(); //清屏

  //英文字符显示，直接用display.println或print显示字符串就行
  //println换行，print不换行
  display.setTextSize(1);             //设置字体大小
  display.setTextColor(WHITE);        //设置字体颜色白色
  display.setCursor(0,0);             //设置字体的起始位置
  display.println("ISDN");   //输出字符并换行
  
  display.setTextColor(BLACK, WHITE); //设置字体黑色，字体背景白色 
  display.println(2400);          //输出数字并换行
  
  display.setTextSize(2);             //设置字体大小
  display.setTextColor(WHITE);        //设置字体白色
  display.println("Xrover");  //输出为ASCII编码的十六进制
  //display.display();                  //显示以上
  
  //中文字符显示
  display.drawBitmap(26, 32, str_1, 16, 16, 1); //在坐标X:26  Y:16的位置显示中文字符凌
  display.drawBitmap(42, 32, str_2, 16, 16, 1); //在坐标X:42  Y:16的位置显示中文字符顺
  display.display();                  //把缓存的都显示
  
  Serial.println("蓝牙连接正常");     //串口监视器显示蓝牙正常状态

  BT.begin(9600);                  //蓝牙通信速率，默认一般为 38400

  pinMode(3, OUTPUT);
  analogWrite(motorPin3, 0);
  analogWrite(motorPin4, 0);
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, 0);
}

void loop()                         
{


  if (Serial.available())           //检测：【串口】如果数据写入，则执行。
  {
    char val = Serial.read();
    Serial.println(val);             //把写入的数据给到自定义变量  X
    BT.println(val);                    //把数据给蓝牙
  }

  if (BT.available())               //检测：【蓝牙】如果数据写入，则执行。
  {
    char sc = BT.read();                  //把检测到的数据给到自定义变量 X
    Serial.println(sc);                //把从蓝牙得到的数据显示到串口监视器

    if (sc == 'w')
    {
      analogWrite(motorPin1, 255);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 255);
      analogWrite(motorPin4, 0);
    }
    if (sc == 'W')
    {
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 0);
      analogWrite(motorPin4, 0);
    }

    if (sc == 's')
    {
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 255);
      analogWrite(motorPin3, 0);
      analogWrite(motorPin4, 255);
    }
    if (sc == 'S')
    {
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 0);
      analogWrite(motorPin4, 0);
    }
    if (sc == 'l')
    {
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 255);
      analogWrite(motorPin3, 255);
      analogWrite(motorPin4, 0);
    }
    if (sc == 'L')
    {
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 0);
      analogWrite(motorPin4, 0);
    }
    if (sc == 'd')
    {
      analogWrite(motorPin1, 255);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 0);
      analogWrite(motorPin4, 255);
    }
    if (sc == 'D')
    {
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 0);
      analogWrite(motorPin4, 0);
    }
    
    
      



  }
}
