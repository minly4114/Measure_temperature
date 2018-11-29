#include <LiquidCrystal.h>
#include <math.h>
String t = " ";
String text= "";
bool isUpClick = false;


LiquidCrystal lcd(8, 9, 4, 5, 6, 7 );

int button;  //вводим числовые значения для кнопок
const int BUTTON_NONE   = 0; //присваиваем постоянное значение для BUTTON_NONE 
const int BUTTON_RIGHT  = 1; //присваиваем постоянное значение для BUTTON_RIGHT
const int BUTTON_UP     = 2; //присваиваем постоянное значение для BUTTON_UP
const int BUTTON_DOWN   = 3; //присваиваем постоянное значение для BUTTON_DOWN 
const int BUTTON_LEFT   = 4; //присваиваем постоянное значение для BUTTON_LEFT
const int BUTTON_SELECT = 5; //присваиваем постоянное значение для BUTTON_SELECT

int getPressedButton() //инициализация переменной
{
  int buttonValue = analogRead(0); // считываем значения с аналогового входа
  if (buttonValue < 100) { //если при нажатии кнопки значение меньше 100
    Serial.print("Right");
    return BUTTON_RIGHT;   // выводим значение BUTTON_RIGHT
  }
  else if (buttonValue < 200) { //если при нажатии кнопки значение меньше 200
    Serial.print("Up");
    return BUTTON_UP; // выводим значение BUTTON_UP
  }
  else if (buttonValue < 400){ //если при нажатии кнопки значение меньше 400
    Serial.print("Down");
    return BUTTON_DOWN; // выводим значение BUTTON_DOWN
  }
  else if (buttonValue < 600){ //если при нажатии кнопки значение меньше 600
    Serial.print("Left");
    return BUTTON_LEFT; // выводим значение BUTTON_LEFT
  }
  else if (buttonValue < 800){ //если при нажатии кнопки значение меньше 800
    Serial.print("Select");
    return BUTTON_SELECT; // выводим значение BUTTON_SELECT
  }
  return BUTTON_NONE; //иначе, выводим значение BUTTON_NONE
}

void setup()
{
  lcd.begin(16, 2);  
  text = "If you wanna measure the temperature - press UP";
  Serial.begin(9600);
  pinMode(12, OUTPUT);
}

void loop()
{ 
  delay(500); 
  button = getPressedButton();
  lcd.scrollDisplayLeft();
  switch(button)
  {
    case BUTTON_UP:
    lcd.clear();
    text = "C or K? Press Left or Right";
    isUpClick = true;
    break;
    case BUTTON_LEFT:
    if(isUpClick)
    {
      buzzer();
      t = (String)temperatureC();
      lcd.clear();
      lcd.print(t + " C");
      delay(5000);
      lcd.clear();
      text = "If you wanna measure the temperature - press UP";
      isUpClick=false;
    }
    break;
    case BUTTON_RIGHT:
    if(isUpClick)
    {
      buzzer();
      t = (String)temperatureF();
      lcd.clear();
      lcd.print(t + " K");
      delay(5000);
      lcd.clear();
      text = "If you wanna measure the temperature - press UP";
      isUpClick=false;
    }
    break;
    case BUTTON_NONE:
      lcd.setCursor(1,0);
      lcd.print(text);
    break;
  }
  
}
void buzzer()
{
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("After the signal, touch the sensor");
    for(int i=0; i<19; i++)
    {
      lcd.scrollDisplayLeft();
      delay(500);
    }
    tone(12,3500,200);
    delay(10000);
    tone(12,3500,200);
}
int temperatureC()
{
  float v = analogRead(A1) * 5.0 / 1024.0;
  float r = v/(5.0 - v);
  float temperature = 1./( 1./(4300)*log(r)+1./(25. + 273.) ) - 273;
  return temperature;
}
int temperatureF()
{
  float v = analogRead(A1) * 5.0 / 1024.0;
  float r = v/(5.0 - v);
  float temperature = 1./( 1./(4300)*log(r)+1./(25. + 273.) );
  return temperature;
}

