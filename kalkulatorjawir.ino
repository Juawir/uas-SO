#include <Keypad.h>
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {A5, A4, A3, A2}; 
byte colPins[COLS] = {11, 10, 9, 8}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

char step;
enum {inAngkaPertama, inAngkaKedua, outHasil};
String strAngkaPertama = "", strAngkaKedua="";
int angkaPertama, angkaKedua;
float hasil;
char operasi;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Robotik ID");
  delay(500);
  lcd.clear();
}

void loop() {
  char customKey = customKeypad.getKey();
  switch(step){
  	case inAngkaPertama:
      if(customKey){
        if(customKey == 'A'){
        	lcd.setCursor(15, 0);
          	lcd.print('+');
          	
          	operasi = '+';
          
          	step = inAngkaKedua;
        }
        else if(customKey == 'B'){
        	lcd.setCursor(15, 0);
          	lcd.print('-');
          
          	operasi = '-';
          
          	step = inAngkaKedua;
        }
        else if(customKey == 'C'){
        	lcd.setCursor(15, 0);
          	lcd.print('x');
          
          	operasi = 'x';
          
          	step = inAngkaKedua;
        }
        else if(customKey == 'D'){
        	lcd.setCursor(15, 0);
          	lcd.print('/');
          
          	operasi = '/';
          
          	step = inAngkaKedua;
        }
        else{
            strAngkaPertama+= customKey;
            lcd.setCursor(0,0);
            lcd.print(strAngkaPertama);
        }
      }
    break;
    
    case inAngkaKedua:
      if(customKey){
        if(customKey == '#'){
          step = outHasil;
        }
        else{
          strAngkaKedua+=customKey;
          lcd.setCursor(0,1);
          lcd.print(strAngkaKedua);
        }
      }
    break;
    
    case outHasil:
        angkaPertama = strAngkaPertama.toInt();
        angkaKedua = strAngkaKedua.toInt();
      
      if (operasi == '+'){
        hasil = angkaPertama + angkaKedua;
      }
      else if (operasi == '-'){
        hasil = angkaPertama - angkaKedua;
      }
      else if(operasi == 'x'){
        hasil = angkaPertama * angkaKedua;
      }
      else if (operasi == '/'){
        hasil = angkaPertama/angkaKedua;
      }
    
    	lcd.setCursor(8, 1);
    	lcd.print(hasil);
    
    if(customKey){
      if(customKey == '*'){
        strAngkaPertama = "";
        strAngkaKedua = "";
        lcd.clear();
        step = inAngkaPertama;
      }
    }
    break;
  }
}