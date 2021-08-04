#include <LiquidCrystal.h>
#include <new>
#include <string.h>
#include <Keypad.h>


#define line1 0
#define line2 1
#define line3 6
#define line4 7


#define column1 8
#define column2 A1
#define column3 A2
#define column4 A3


#define pin_R 13
#define pin_G 10
#define pin_B 9


LiquidCrystal lcd(12,11,5,4,3,2);

const byte qtd_lines = 4;
const byte qtd_columns = 4;

char keys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pines_lines[4] = {line1, line2, line3, line4};
byte pines_columns[4] = {column1, column2, column3, column4};


String player_name;
char *vector = new char[6];


void sortValue(int *random_choice){
  *random_choice = random(6);
}


void set_name(char *characters[6], String *player_name){
  Keypad keypad = Keypad(makeKeymap(keys), pines_lines, pines_columns, qtd_lines, qtd_columns);
  int counter = 0;
  while(1){
    if (counter > 5){
      break;
    }
    lcd.setCursor(0,0);
    lcd.print("username:");
    char key_pressed = keypad.getKey();
    if (key_pressed){
        delay(500);
        lcd.setCursor(counter, counter+2);
        lcd.print(key_pressed);
        *characters[counter] = key_pressed;
        *player_name += key_pressed;
        counter++;
        delay(100);
      
      }
      
    }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.clear();
    
  }


bool chooseColor(char options[3], char combination[3]){
  Keypad keypad = Keypad(makeKeymap(keys), pines_lines, pines_columns, qtd_lines, qtd_columns);
  int counter = 0;
  while (1){
    if (counter > 2){
      break;
    }
    
    char key_pressed = keypad.getKey();

    if (key_pressed){
      switch(key_pressed){
        case '0':
          options[counter] = 'R';
          break;
        case '1':
          options[counter] = 'G';
          break;
        case '2':
          options[counter] = 'B';
          break;
        case '3':
          options[counter] = 'Y';
          break;
        case '*':
          options[counter] = 'P';
          break;
        case '#':
          options[counter] = 'A';
          break;
      }
      Serial.println(key_pressed);
      Serial.println(options[counter]);
      delay(300);
      lcd.setCursor(12,1);
      lcd.print(options[counter]);
      counter++;
    }
    
    
  }
  for (int aux=0; aux < 3; aux++){
    if (options[aux] != combination[aux]){
        setColor(255,0,0);
        return false;
        break;
    }
  }
  return true;
}


void setColor(int R, int G, int B){

  analogWrite(pin_R, R);
  analogWrite(pin_G, G);
  analogWrite(pin_B, B);
  delay(1000);
  analogWrite(pin_R, 0);
  analogWrite(pin_G, 0);
  analogWrite(pin_B, 0);
  delay(500);
  
}
 



void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(pin_R, OUTPUT);
  pinMode(pin_G, OUTPUT);
  pinMode(pin_B, OUTPUT);
  
  randomSeed(analogRead(A0));
  lcd.clear();
  
}

void loop()
{
  int random_choice, val, score;
  set_name(&vector, &player_name);
  lcd.clear();
  Serial.println(player_name);
  char *lista[3] = {"@", "#", "$"};
  char combination[3];
  char playerCombination[3];
  const int combinations[6][3] = {
    {255, 0, 0}, //RED;
    {0, 255, 0}, //GREEN;
    {0, 0, 255}, //BLUE;
    {255, 255, 0}, //YELLOW;
    {80, 0, 80}, //PURPLE;
    {0, 255, 255} //AQUA
  };
  
  
while (1){
  
  for (int aux=0; aux < 3; aux++){
    
    lcd.clear();
    lcd.setCursor(8,2);
    
    sortValue(&random_choice);
    Serial.println(aux);
    
    switch(random_choice){
      case 0:
          combination[aux] = 'R';
          setColor(combinations[0][0], combinations[0][1], combinations[0][2]);
          lcd.print("R");
          delay(300);
          break;
      case 1:
          combination[aux] = 'G';
          setColor(combinations[1][0], combinations[1][1], combinations[1][2]);
          lcd.print("G");
          delay(300);
          break;
      case 2:
          combination[aux] = 'B';
          setColor(combinations[2][0], combinations[2][1], combinations[2][2]);
          lcd.print("B");
          delay(300);
          break;
      case 3:
          combination[aux] = 'Y';
          setColor(combinations[3][0], combinations[3][1], combinations[3][2]);
          lcd.print("Y");
          delay(300);
          break;
      case 4:
          combination[aux] = 'P';
          setColor(combinations[4][0], combinations[4][1], combinations[4][2]);
          lcd.print("P");
          delay(300);
          break;
      case 5:
          combination[aux] = 'A';
          setColor(combinations[5][0], combinations[5][1], combinations[5][2]);
          lcd.print("A");
          delay(300);
          break;
    }
    
  }
  lcd.clear();
  lcd.clear();
  
  delay(1000);
  int counter = 0;
  bool verifier;
  
  
  
  lcd.setCursor(0,0);
  
  
  lcd.print("0-R 1-G 2-B");
  
  lcd.setCursor(0,2);
  
  lcd.print("3-Y *-P #-A");
  
  lcd.setCursor(12, 0);
  
  lcd.print(score);
  
  verifier = chooseColor(playerCombination, combination);
  
  if (verifier == false){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("VOCE PERDEU!!!");
    delay(3000);
    lcd.clear();
    delay(1000);
    break;
  }
  score++;
  
  }
}