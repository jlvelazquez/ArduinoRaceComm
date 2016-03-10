/*
 * 
 * Arduino Race Computer
 * 
 * @autor: jlvelazquez
 * https://github.com/jlvelazquez/ArduinoRaceComm
 * 
 * 

  The LCD circuit:
  
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include <Chrono.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Buzzer
const int Buzzer1 = 9;

//Declare menú options
int currentMenu = 0;
String menu[9] = { "Race Time", "Driver Time", "Box", "Info carrera", "Si", "No", "Salida de pista", "Problema leve", "Problema grave"};
#define MENU_LENGTH 9;
String messages[5] = { "Seleccionado 01", "Seleccionado 02", "Seleccionado 03", "Seleccionado 04", "Seleccionado 05",  };
int threshold = 201; // Joystick movement threshold that fires menu scrolling;

//ToDo: implements Race Time and Driver Time using Chrono Library. Maybe migrating to Arduino's milis()
Chrono myChrono(Chrono::SECONDS);
unsigned long elapsed = myChrono.elapsed();

void setup() {
  pinMode(Buzzer1, OUTPUT);
  Serial.begin(9600);
  charsFactory();
  welcomeMsg();
  myChrono.start();
}

void welcomeMsg(){
  lcd.begin(16, 2);
  lcd.print("  Colomo's Team  ");
  lcd.setCursor(0,1);
  lcd.print("      SAAB      ");
}

void initMenu(){  
  lcd.clear();
  lcd.write(byte(0));
  lcd.setCursor(1,0);
  lcd.print(menu[currentMenu]);
  lcd.setCursor(1,1);
  lcd.print(menu[currentMenu + 1]);
}

byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};
byte bullet[8] = {
  B00000,
  B00000,
  B00000,
  B01110,
  B01010,
  B01110,
  B00000,
  B00000
};
byte arrow[8]{0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};
void charsFactory(){
   lcd.createChar(0, arrow);
}

void playTone(int vol){
  if(vol == 0){
    tone(Buzzer1,200,5);
  }else{
    tone(Buzzer1,900,50);
  }
}

void joystickController(){
    int ejeY = analogRead(A1);
    int ejeX = analogRead(A2);
    if(ejeY > 900 && threshold > 200){
      textScroller(1);
      threshold = ejeY;
    }else if(ejeY < 100 && threshold > 200){
      textScroller(0);
      threshold = ejeY;
    }
    if(ejeX > 900 && threshold > 200){
      textScroller(2);
      threshold = ejeY;
    }else if(ejeX < 100 && threshold > 200){
      textScroller(2);
      threshold = ejeY;
    }
    delay(300);
    if(threshold <= 200){
       threshold = 201;
    }
}

int lastDir = 0;

void textScroller(int dir) {
  lcd.setCursor(1, 0);
  lcd.print("                ");
  lcd.setCursor(1, 1);
  lcd.print("                ");
  if(dir == 0){ // DOWNWARDS
      playTone(0);
      if(currentMenu < MENU_LENGTH - 1){
        currentMenu = currentMenu + 1;
      }
      lcd.setCursor(1,0);
      lcd.print(menu[currentMenu]);
      if(currentMenu < MENU_LENGTH - 1){
        lcd.setCursor(1,1);
        lcd.print(menu[currentMenu + 1]);
      }
  } else if(dir == 1) { // UPWARDS
      playTone(0);
      if(currentMenu > 0){
        currentMenu = currentMenu - 1;
      }
      lcd.setCursor(1,0);
      lcd.print(menu[currentMenu]);
      lcd.setCursor(1,1);
      lcd.print(menu[currentMenu + 1]);
      
  }else if(dir == 2) { // BOTH LEFT OR RIGHT. SELECT OPTION
    
    selectMenuItem();
    
  } else { // BACK TO PREVIOUS STATE
    
    lcd.write(byte(0));
    lcd.setCursor(1,0);
    lcd.print(menu[currentMenu]);
    if(currentMenu < MENU_LENGTH - 1){
      lcd.setCursor(1,1);
      lcd.print(menu[currentMenu + 1]);
    }
  }
  if(currentMenu > MENU_LENGTH - 1){
    currentMenu = MENU_LENGTH - 1;  
  }
  if(currentMenu < 0){
    currentMenu = 0;  
  }
  //updateDisplay();
}

void selectMenuItem() {
  playTone(1);
  lcd.setCursor(1,0);
  lcd.blink();
  lcd.print("Enviando"); 
  delay(200);
  lcd.setCursor(9,0);
  lcd.print("."); 
  delay(200);
  lcd.setCursor(10,0);
  lcd.print("."); 
  delay(200);
  lcd.setCursor(11,0);
  lcd.print("."); 
  delay(1500);
  //lcd.print(messages[currentMenu]); 
  lcd.setCursor(1,0);
  playTone(0);
  lcd.print("Mensaje enviado"); 
  lcd.noBlink();
  delay(1200);
  textScroller(3);
}

int begin = 0;

void animateIntro() {
  if(begin == 0){
    delay(2000);
    for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
      lcd.scrollDisplayLeft();
      delay(150);
    }
    delay(1000);
    begin = 1;
    lcd.clear();
   // initMenu(); //UNCOMMENT TO SEE MENU. COMMENT TO SEE PREVIEW OF CHRONO
  }
}

void convertToHours() {
  
}

void loop() {
  animateIntro();
  joystickController();
  lcd.setCursor(0,0);
  convertToHours();
  elapsed = myChrono.elapsed();
  lcd.print(elapsed);  
}

