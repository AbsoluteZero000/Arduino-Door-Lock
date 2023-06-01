#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

int hours = 0, mins = 0,  sec = 0;
double startmillisec;

const byte Rows = 4;
const byte Cols = 4;
const byte passcodeSize = 4;
char passcode[passcodeSize] = {'1', '9', '0', '5'};
int counter = 0;

int servopin = 6;
byte rowpins[Rows] = {30, 31, 32, 33};
byte colspins[Cols] = {34, 35, 36, 37};


char PadKeys[Rows][Cols]= {
{'1' , '2' , '3' , '&'},
{'4' , '5' , '6' , 'B'},
{'7' , '8' , '9' , 'C'},
{'*' , '0' , '#' , 'D'}
};

Keypad SecInput = Keypad(makeKeymap(PadKeys), rowpins, colspins, Rows, Cols);
Servo lockcontroller;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void openthedoor(){
    lcd.clear();
    lcd.print("Welcome Back");
    lcd.setCursor(3,1);
    lcd.print("Hackster");
    lockcontroller.write(0);
    delay(3000);
    
}
void lockthedoor(){
    lcd.clear();
    lcd.print("Cya Later");
    lcd.setCursor(3,1);
    lcd.print("Hackster");
    lockcontroller.write(180);
    delay(3000);
    startmillisec =  millis();
    
}
void getstatus(){
  sec = (int((millis()-startmillisec)/1000));
  mins = sec/60;
  hours = mins/60;
  sec  = sec%60;
  mins =  mins%60;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("last opened was:");
  lcd.setCursor(1,1);
  lcd.print(hours);
  lcd.print(":");
  lcd.print(mins);
  lcd.print(":");
  lcd.print(sec);
  lcd.print(" ago");
  delay(3000);
}

void setupLCD(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hello Hackster");
    lcd.setCursor(0, 1);
    lcd.print("PassCode : ");
}


void setup() {

  lockcontroller.attach(servopin);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lockcontroller.write(0);

}

void loop() {
  
  
  setupLCD();
  counter = 0;
  while(true){

      char customKey = SecInput.getKey();
      if(customKey  ==  '&' && customKey){
        lockthedoor();
        break;
      }
      
      if(customKey  ==  'B' && customKey){
        getstatus();
        break;
      }
      if(customKey){
        
        Serial.println(customKey);
     

        if(customKey == passcode[counter]){
          
          lcd.setCursor(11+counter, 1);
          lcd.print(customKey);
          delay(100);
          counter++;
          
          if(counter == 4){
            openthedoor();
            break;
          }
        }
        else{
          lcd.clear();
          lcd.print("InCorrect");
          lcd.setCursor(4,1);
          lcd.print("PassCode");
          delay(3000);
          break;
        }
      }
    }
    
}

