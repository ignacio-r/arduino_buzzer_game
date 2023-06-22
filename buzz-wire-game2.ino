#include <LiquidCrystal_I2C.h>

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3F,16,2);

const int GREEN_LED = 12;
const int RED_LED = 13;
const int CIRCUIT = 9;
const int BUTTON = 2;

int gameInit = false;
int strikes = 0;
int gameWin = false;

unsigned long previousMillis = 0; // time last changed
const long interval = 1000; // interval between countdown
int count = 20; // challenge mode timer

unsigned long previousMillis2 = 0; // time last changed
const long interval2 = 200; // interval between countdown
bool greenOn = false;

void setup() {
  pinMode(CIRCUIT, INPUT); // setup circuit
  pinMode(BUTTON, INPUT); // setup button
  
  pinMode(GREEN_LED, OUTPUT); // setup green led
  pinMode(RED_LED, OUTPUT); // setup red led

  lcd.init(); // setup LCD
  lcd.backlight(); //Encender la luz de fondo.
}

void loop() {
  if(!gameInit) {
    if(!gameWin) { 
      clickToPlay();
      if(digitalRead(BUTTON) == HIGH) {
        gameInit = true;
      }
    } else {
      youWin();
    }
  }
  else {
    showCountdown();
    if(count <= 0) {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      printGameOver();
      resetGame();
    }
    if(digitalRead(CIRCUIT) == HIGH) {
      strikes++;
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      if(strikes >= 3) {
        printGameOver();
        resetGame();
      }
      delay(200);
    }
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    if(digitalRead(BUTTON) == HIGH) {
      gameInit = false;
      gameWin = true;
    }
  }
}

void resetGame() {
  gameInit = false;
  gameWin = false;
  lcd.clear();
  strikes = 0;
  count = 20;
  greenOn = false;
}

void clickToPlay() {
  lcd.setCursor(0, 0);
  lcd.print("Click the button");
  lcd.setCursor(0, 1);
  lcd.print("to PLAY!");
  unsigned long currentMillis = millis(); // current time
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;
    if(greenOn){
      digitalWrite(GREEN_LED, LOW);
      greenOn = false;
    } else {
      digitalWrite(GREEN_LED, HIGH);
      greenOn = true;
    }
  }
}

void youWin() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You WIN!");
  printSeconds();
  resetGame();
}

void showCountdown() {
  String strikesText = "Strikes: " + String(strikes) + "/3";
  lcd.setCursor(0,0);
  lcd.print(strikesText);

  String countText = String(count) + " seconds";
  lcd.setCursor(0,1);
  lcd.print(countText);
  delay(100);

  unsigned long currentMillis = millis(); // current time
  if (currentMillis - previousMillis >= interval) {
    lcd.clear();
    previousMillis = currentMillis;
    count--;
  }
}

void printGameOver() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GAME OVER");
  printSeconds();
}

void printSeconds() {
  for(int i = 5; i >= 1; i--) {
    String text = "Wait " + String(i) + " seconds.";
    lcd.setCursor(0,1);
    lcd.print(text);
    delay(1000);
  }
}