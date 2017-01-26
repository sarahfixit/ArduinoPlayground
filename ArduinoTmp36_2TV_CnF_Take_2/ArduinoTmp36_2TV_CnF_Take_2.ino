#include <TVout.h>
#include <video_gen.h>



//#include "TVout.h"
#include "fontALL.h"
#include "thermometer.h"

const float SUPPLY_VOLTAGE = 5.0;
const float MIN_C_TEMP = 5.5;
const float MAX_C_TEMP = 40.0;
const float MIN_F_TEMP = 0.0;
const float MAX_F_TEMP = 120;
const unsigned int SCREEN_WIDTH = 120;
const unsigned int SCREEN_HEIGHT = 96;
const unsigned int TEMP_SENSOR_PIN = A1;
const unsigned int SCALE_X_MIN = 8;
const unsigned int SCALE_Y_MIN = 6;
const unsigned int SCALE_Y_MAX = 75;
const unsigned int SCALE_WIDTH = 3;
const unsigned int SCALE_HEIGHT = SCALE_Y_MAX - SCALE_Y_MIN;

float current_temperature = 0.0;

unsigned long last_measurement = millis();
TVout TV;

//declare functions
const float mapfloat (float, float, float, float, float);
const float get_temperature();

void setup() {
  TV.begin(NTSC, SCREEN_WIDTH, SCREEN_HEIGHT);
  TV.bitmap(0, 1, thermometer);
  TV.select_font(font4x6);
  /*
   * 
   TV.set_cursor(20, 4);
  TV.print("40");
  TV.set_cursor(20, 24);
  TV.print("30");
  TV.set_cursor(20, 44);
  TV.print("20");
  TV.set_cursor(20, 64);
  TV.print("10");
  */
}

void loop() {
  unsigned long current_millis = millis();
//if   (abs(current_millis - last_measurement) >= 1000) 


    current_temperature = get_temperature();
    float current_F_temperature = ((current_temperature *1.8) +32);
    last_measurement = current_millis;

    //setup for C

    TV.set_cursor(20, 4);
    TV.print("40");
    TV.set_cursor(20, 24);
    TV.print("30");
    TV.set_cursor(20, 44);
    TV.print("20");
    TV.set_cursor(20, 64);
    TV.print("10");

    
    
    
    //do celcius
    
    int y_pos = mapfloat(current_temperature, MIN_C_TEMP, MAX_C_TEMP, SCALE_Y_MAX, SCALE_Y_MIN);
   // TV.draw_rect( SCALE_X_MIN, SCALE_Y_MIN, SCALE_WIDTH, SCALE_HEIGHT, BLACK, BLACK);
   
    TV.select_font(font6x8);
    TV.set_cursor(53, 1);
    TV.print("Current");
    TV.set_cursor(40, 13);
    TV.print("Temperature:");
    TV.select_font(font8x8);
    TV.set_cursor(50, 25);
    TV.print(current_temperature, 1);
    TV.print(" C");
    TV.draw_circle(88, 27, 1, WHITE); 
     TV.draw_rect(
      SCALE_X_MIN, y_pos, SCALE_WIDTH, SCALE_Y_MAX - y_pos, WHITE, WHITE);

      
    //delay X seconds
    delay(50000);
    
   

    
    //rinse & repeat for farenheit
    //setup for F
    //note 0*-120*
  
    TV.set_cursor(20, 4);
    TV.print("120");
    TV.set_cursor(20, 24);
    TV.print("80");
    TV.set_cursor(20, 44);
    TV.print("40");
    TV.set_cursor(20, 64);
    TV.print("0");
  

   //do farenheit
   
    y_pos = mapfloat(current_F_temperature, MIN_F_TEMP, MAX_F_TEMP, SCALE_Y_MAX, SCALE_Y_MIN);
    //TV.draw_rect( SCALE_X_MIN, SCALE_Y_MIN, SCALE_WIDTH, SCALE_HEIGHT, BLACK, BLACK);
    TV.draw_rect( SCALE_X_MIN, y_pos, SCALE_WIDTH, SCALE_Y_MAX - y_pos, WHITE, WHITE);
    TV.select_font(font6x8);
    TV.set_cursor(53, 1);
    TV.print("Current");
    TV.set_cursor(40, 13);
    TV.print("Temperature:");
    TV.select_font(font8x8);
    TV.set_cursor(50, 25);
    
    TV.print(current_F_temperature, 1);
    TV.print(" F");
    TV.draw_circle(88, 27, 1, WHITE); 
      
    //delay X seconds
    delay(50000);

   
}

const float mapfloat(
  float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

const float get_temperature() {

  
  //work on tweaking this to get a somewhat accurate reading...
  
  const int sensor_voltage = analogRead(TEMP_SENSOR_PIN);
  const float voltage = sensor_voltage * SUPPLY_VOLTAGE / 1024;
  return (voltage * 1000 - 500) / 100; //divide by ONE HUNDRED, not by ten.
}




