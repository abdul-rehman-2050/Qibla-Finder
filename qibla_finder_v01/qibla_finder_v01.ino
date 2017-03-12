/*
Qibla Finding App- 
V0.1
Arduino Mega
Started at: 12-MAR-2017, 5:18PM

*/

//===========================================================================

#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>


//===========================================================================

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin



#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//===========================================================================

void setup() {
  uint16_t width=0,height=0,cx=0,cy=0;
  
  
  Serial.begin(9600);   
  tft.reset();  
  uint16_t identifier = tft.readID();
  Serial.println(identifier);
  tft.begin(identifier);  
  tft.setRotation(0); 
  tft.fillScreen(BLACK);
  tft.setCursor(25, 7);
  tft.setTextColor(WHITE);  
  tft.setTextSize(2);
  //tft.println("Qibla Direction");

  width=tft.width();
  height=tft.height();
  cx=width/2; cy=height/2;
  tft.drawCircle( cx,150,115,BLUE);
  tft.fillCircle( cx,150,110,BLACK);
  tft.drawCircle( cx,150,5,RED);

  
  tft.setTextSize(4);
  tft.setTextColor(RED);  
  tft.setCursor(cx-10, 40);  
  tft.println("N");
  tft.setCursor(cx-10, 240);
  tft.println("S");
  tft.setCursor(width-30, 135);  
  tft.println("E");
  tft.setCursor(15, 125);
  tft.println("W");


  
}//setup ends here
//===========================================================================

void loop() {
  // put your main code here, to run repeatedly:


  

}//loop Ends here
//===========================================================================
