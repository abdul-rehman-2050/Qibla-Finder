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

#include <Wire.h>
#include <HMC5883L.h>


//===========================================================================

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET 10 // Can alternately just connect to Arduino's reset pin



#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
HMC5883L compass;
//===========================================================================
 uint16_t width=0,height=0,cx=0,cy=0;
void setup() {
 
  
  
  Serial.begin(9600);   


 while (!compass.begin())
  {
    Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
    delay(500);
  }
// Set measurement range
  compass.setRange(HMC5883L_RANGE_1_3GA);

  // Set measurement mode
  compass.setMeasurementMode(HMC5883L_CONTINOUS);

  // Set data rate
  compass.setDataRate(HMC5883L_DATARATE_30HZ);

  // Set number of samples averaged
  compass.setSamples(HMC5883L_SAMPLES_8);

  // Set calibration offset. See HMC5883L_calibration.ino
  compass.setOffset(0, 0);



  
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
  tft.setCursor(15, 135);
  tft.println("W");


  
}//setup ends here
//===========================================================================

void loop() {
  Vector norm = compass.readNormalize();

  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);

  // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // (+) Positive or (-) for negative
  // For Bytom / Poland declination angle is 4'26E (positive)
  // Formula: (deg + (min / 60.0)) / (180 / M_PI);
  float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;

  // Correct for heading < 0deg and heading > 360deg
  if (heading < 0)
  {
    heading += 2 * PI;
  }

  if (heading > 2 * PI)
  {
    heading -= 2 * PI;
  }

  // Convert to degrees
  float headingDegrees = heading * 180/M_PI; 

  // Output
  Serial.print(" Heading = ");
  Serial.print(heading);
  Serial.print(" Degress = ");
  Serial.print(headingDegrees);
  Serial.println();

  
  tft.fillRect(20,270,200,35,BLACK);
  tft.setTextSize(1);
  tft.setTextColor(WHITE);
  tft.setCursor(25, 295);
  tft.print("H=");
  tft.print(heading);
  tft.print(", D=");
  tft.print(headingDegrees);
  tft.fillCircle( cx,150,55,RED);
  tft.setTextSize(3);
 
  if(heading>0.3 && heading < 0.9)
  {
    //tft.setTextSize(2);
    //tft.setTextColor(YELLOW);
    //tft.setCursor(cx-40, 120);
    //tft.print("Qibla");
    //tft.setCursor(cx-20,160);    
    //tft.print("Found");


   // tft.drawFastVLine(cx-40,120,40,BLACK);
    //tft.drawFastVLine(cx+20,120,40,BLACK);
    //tft.drawFastVLine(cx,100,60,BLACK);

    tft.fillRect(cx-25,120,50,60,BLACK);
    tft.fillRect(cx-25,132,50,7,YELLOW);
    tft.fillRect(cx-23,145,3,7,YELLOW);
    tft.fillRect(cx-14,145,9,7,YELLOW);
    tft.fillRect(cx,145,6,7,YELLOW);
    tft.fillRect(cx+12,145,10,7,YELLOW);
    


    
    
  }
  else 
  {
    
     tft.setTextColor(WHITE);
     tft.setCursor(cx-40, 150);
    tft.print(heading);
  
  }
  delay(1000);


  

}//loop Ends here
//===========================================================================
