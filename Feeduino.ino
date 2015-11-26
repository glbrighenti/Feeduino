#include <LiquidCrystal.h>
#include <Servo.h>
LiquidCrystal lcd(12,11,5,4,3,2);



const int pinButtonHours = 13;    
const int pinButtonMin = 8;    
int buttonHourState = 0;  
int buttonMinuteState = 0;        
String strConvertTime ; 
bool updateLcd=false;
long lastTime=0; 

int minutes=0;
int hours =0;
Servo myservo;
bool isFeeding=false;

void setup() {
  
  lastTime=millis();
  pinMode(pinButtonHours, INPUT);
  pinMode(pinButtonMin, INPUT);   
  lcd.begin(16,2);
  lcd.clear();
  printTime();
  myservo.attach(9);
  myservo.write(5);


}

void loop() {

  readButtons();

  calculateTime();

  if(updateLcd){
    printTime();
    updateLcd=false;
  }
  
}

void calculateTime(){

  if ((millis() - lastTime) > 60000) {//each minute
    lastTime=millis() ;
    addMinute();
    updateLcd=true;
  }
}
  


void readButtons(){
  
  buttonHourState = digitalRead(pinButtonHours);
  if (buttonHourState == HIGH) {
    delay(120);
    addHour();
    updateLcd=true;
  }

  buttonMinuteState = digitalRead(pinButtonMin);
  if (buttonMinuteState == HIGH) {
    delay(120);
    addMinute();
    updateLcd=true;
  }
}


void printTime(){
 lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hora atual ");
  strConvertTime=String(hours, DEC);
  if(hours<10){
    lcd.print("0");
  }
  lcd.print(strConvertTime);
  lcd.print(":");
  if(minutes<10){
    lcd.print("0");
  }
  strConvertTime=String(minutes, DEC);
  lcd.print(strConvertTime);

  lcd.setCursor(0,0);

}

void addHour(){
  hours++;
 if(hours==24){
    hours=0;
  }
 
}


void addMinute(){
  minutes++;
  if(minutes==60){
    minutes=0;
    addHour();
  }
  checkFeedTime();
}

 void checkFeedTime(){
    
    if(isFeeding){
      return;
    }
    if(minutes!=0){
      return;
    }
    
    if((hours==8) || (hours==12) || (hours==19)){
      startFeeding();
    }
  }


void startFeeding(){
  isFeeding=true;
  myservo.write(90);
  delay(5000);
  myservo.write(5);
  isFeeding=false;
  
}

