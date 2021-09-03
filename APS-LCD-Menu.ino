
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int buttonPin1 = 2, buttonPin2 = 3; 
const int buttonPin3 = 4;    // the number of the pushbutton pin
int buttonState1 = 0, buttonState2 = 0;
int buttonState3 = 0;        // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int count_value = 0, buc_value = 0, beam_value = 0;
int prestate1 = 0, prestate2 = 0, prestate3 = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // initialise Button Pins
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  // initialize the LCD
  lcd.begin();
  lcd.backlight();
  WelcomeMsg();
}

void loop() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3); 
   
  displayVal();
  select();
  bucSelect();
  beamSelect();
  beamSelectReverse();
  reset();
}

void WelcomeMsg() {
  lcd.setCursor(1,0);
  lcd.print("Auto-pointing");
  lcd.setCursor(0,1);
  lcd.print("Satellite System");
  delay(3000);
  lcd.clear();
}

void displayVal(){
  lcd.setCursor(1,0);
  lcd.print("BUC:");
  lcd.setCursor(7,0);
  lcd.print(buc_value);  
  lcd.setCursor(1,1);
  lcd.print("Beam:");
  lcd.setCursor(7,1);
  lcd.print(beam_value);  
}

void bucSelect(){
  if(buttonState1 == HIGH && prestate1 == 0 && count_value % 2){
    buc_value++;
    lcd.setCursor(7,0);
    lcd.print("   ");
    lcd.setCursor(7,0);
    lcd.print(buc_value);
  }
  else if(buttonState2 == HIGH && prestate2 == 0 && count_value % 2){
    buc_value--;
    lcd.setCursor(7,0);
    lcd.print("   ");
    lcd.setCursor(7,0);
    lcd.print(buc_value);
  }
}

void beamSelect(){
  if(buttonState1 == HIGH && prestate1 == 0 && (count_value % 2) == 0){
    beam_value++;
    lcd.setCursor(7,1);
    lcd.print("    ");
    lcd.setCursor(7,1);
    lcd.print(beam_value);
  }
  else if(buttonState2 == HIGH && prestate2 == 0 && (count_value % 2) == 0){
    beam_value--;
    lcd.setCursor(7,1);
    lcd.print("    ");
    lcd.setCursor(7,1);
    lcd.print(beam_value);
  }
}

void beamSelectReverse(){
  if (beam_value <= 0){
    beam_value = 71;
  }
  else if (beam_value >= 72){
    lcd.setCursor(7,1);
    lcd.print("   ");
    beam_value = 1;
  }
}

void select(){
  if(buttonState3 == HIGH && prestate3 == 0) {
    count_value++;
    if (count_value % 2){
      lcd.setCursor(0,1);
      lcd.print(" ");
      lcd.setCursor(0,0);
      lcd.print(">");
      prestate3 = 1;
    }
    else if ((count_value % 2) == 0) {
      lcd.setCursor(0,0);
      lcd.print(" ");
      lcd.setCursor(0,1);
      lcd.print(">");
    }
     prestate3 = 1;
  }     
}

void reset(){
  prestate1 = 0;
  prestate2 = 0;
  prestate3 = 0;
  if (buc_value < 0){
    buc_value = 0;
    lcd.setCursor(7,0);
    lcd.print("   ");
  }
  delay(100);
}
