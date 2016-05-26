#include <Wire.h>
#include "rgb_lcd.h"
#include <math.h>

rgb_lcd lcd;


//Configuration
const int buttonPin = 8;
int buttonState = 0; 
const int ledPin =  4;

//Global variables
struct {
  int x = 0;
  int y = 1;
} player;

struct {
  int x = 0;
  int y = 1;
} enemy;

int speed = 300;
boolean alive = true;
int wait = 0;
int level = 0;
boolean reset = false;
int colorselector = 0;
int colors[] = {
  204, 204, 0, //red
  102, 204, 0, //green
  0, 204, 102, //less green
  0, 204, 204, //blue
  0, 0, 204, //more blue
  102, 0, 204, //more blue
  204, 0, 204, //pink
  204, 0, 102, //more blue
};
int back_down = 0;


//GAME
void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop()
{
    if(reset){
      alive = true;
      speed = 300;
       alive = true;
      wait = 0;
      level = 0;
      reset = false;
      colorselector = 0;
    }
   
    for (int thisChar = 15; alive && thisChar >= 0; thisChar--)
    {
        lcd.clear();

        //screen color
        lcd.setRGB(colors[colorselector], colors[colorselector+1], colors[colorselector+2]); //screen color
        
        
        lcd.setCursor(8, 0);
        lcd.print("Level ");
        lcd.setCursor(14, 0);
        lcd.print(level);
       
        enemy.x = thisChar;
        if (back_down) --back_down; 
        if(wait != 0) {   //keeping the jump
          player.x = 0;
          --wait;
          if(wait == 0) back_down = 2; //back to ground
        }
        else {
          player.y = 1;
         
        }

         buttonState = digitalRead(buttonPin);
        //Play
        if (buttonState == HIGH && wait == 0 && !back_down) {
          digitalWrite(ledPin, HIGH);
          player.y = 0; //jump
          wait = 1;
        }
        
        
        //print
        lcd.setCursor(enemy.x, enemy.y);
        lcd.print('Y');
        lcd.setCursor(player.x, player.y);
        lcd.print('x');
        delay(speed);
       

        //set Game Over
        if (player.x == enemy.x && player.y == enemy.y)  alive = false;
    }
    
    if(speed > 100) speed -= 20; //increase difficulty
    else if(speed > 50) speed -= 5;
    ++level;
    colorselector += 3;
        if(colorselector > 23) colorselector = 0;

    //Game Over
    if(!alive) {
      for(int size = 15; size >= 0 && !reset; size--) {
        buttonState = digitalRead(buttonPin);
        if (buttonState == HIGH) reset = true;
        lcd.clear();
        lcd.setCursor(size, 0);
        lcd.print("GAME OVER");
        lcd.setCursor(3, 1);
        lcd.print("By Marc Soler");
        //lcd.setRGB(colors[0].x, colors[0].y, colors[0].z);
        //lcd.setRGB(colors.x, 0, 0);
        lcd.setRGB(204, 0, 0);
        delay(300);
      }
    }
    
    

}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
