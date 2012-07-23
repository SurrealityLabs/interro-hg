#include <Bounce.h>

Bounce Player1Button = Bounce(8, 10);
#define Player1LED 8
Bounce Player2Button = Bounce(7, 10);
#define Player2LED 7
Bounce Player3Button = Bounce(6, 10);
#define Player3LED 6
Bounce Player4Button = Bounce(5, 10);
#define Player4LED 5
Bounce Player5Button = Bounce(14, 10);
#define Player5LED 14
Bounce Player6Button = Bounce(4, 10);
#define Player6LED 4
Bounce Player7Button = Bounce(3, 10);
#define Player7LED 3
Bounce Player8Button = Bounce(2, 10);
#define Player8LED 2

Bounce ResetButton = Bounce(16, 10);

#define toneOutput 10
#define readyOutput 9

const long toneLength = 500;
const long autoResetLength = 10000;
const int autoResetDelay = 5000;
const int playerTones[] = {
  0, 2000, 2000, 2000, 2000, 2400, 2400, 2400, 2400};

uint8_t currentState = 0;

void setup(void) {
  enablePlayers();
  pinMode(16, INPUT);

  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop(void) {
  static uint8_t activePlayer = 0;
  static long toneStartTime = 0;
  static long autoResetStart = 0;

  ResetButton.update();

  if(ResetButton.fallingEdge()) {
    currentState = 0;
  }

  switch(currentState) {
  case 0:
    noTone(toneOutput);
    enablePlayers();
    digitalWrite(readyOutput, 1);
    activePlayer = 0;

    Player1Button.update();
    Player2Button.update();
    Player3Button.update();
    Player4Button.update();
    Player5Button.update();
    Player6Button.update();
    Player7Button.update();
    Player8Button.update();

    toneStartTime = millis() + toneLength;

    if(Player1Button.fallingEdge()) {
      activePlayer = 1;
      currentState = 1;
    } 
    else if(Player2Button.fallingEdge()) {
      activePlayer = 2;
      currentState = 1;
    } 
    else if(Player3Button.fallingEdge()) {
      activePlayer = 3;
      currentState = 1;
    } 
    else if(Player4Button.fallingEdge()) {
      activePlayer = 4;
      currentState = 1;
    } 
    else if(Player5Button.fallingEdge()) {
      activePlayer = 5;
      currentState = 1;
    } 
    else if(Player6Button.fallingEdge()) {
      activePlayer = 6;
      currentState = 1;
    } 
    else if(Player7Button.fallingEdge()) {
      activePlayer = 7;
      currentState = 1;
    } 
    else if(Player8Button.fallingEdge()) {
      activePlayer = 8;
      currentState = 1;
    } 
    else {
      activePlayer = 0;
      currentState = 0;
    }
    break;
  case 1:
    setPlayerTone(activePlayer);
    setPlayerLEDs(activePlayer);
    digitalWrite(readyOutput, 0);

    if(millis() - toneStartTime >= toneLength) {
      currentState = 2;
      autoResetStart = millis();
    } 
    else {
      currentState = 1;
    }

    break;
  case 2:
    noTone(toneOutput);
    setPlayerLEDs(activePlayer);
    digitalWrite(readyOutput, 0);

    if(millis() - autoResetStart >= autoResetLength) {
      currentState = 0;
    } 
    else {
      currentState = 2;
    }

    break;
  default:
    currentState = 0;
    break;
  }
}

void setPlayerTone(uint8_t playerNum) {
  tone(toneOutput, playerTones[playerNum]);
}

void setPlayerLEDs(uint8_t playerNum) {
  digitalWrite(Player1LED, 1);
  pinMode(Player1LED, OUTPUT);
  digitalWrite(Player2LED, 1);
  pinMode(Player2LED, OUTPUT);
  digitalWrite(Player3LED, 1);
  pinMode(Player3LED, OUTPUT);
  digitalWrite(Player4LED, 1);
  pinMode(Player4LED, OUTPUT);
  digitalWrite(Player5LED, 1);
  pinMode(Player5LED, OUTPUT);
  digitalWrite(Player6LED, 1);
  pinMode(Player6LED, OUTPUT);
  digitalWrite(Player7LED, 1);
  pinMode(Player7LED, OUTPUT);
  digitalWrite(Player8LED, 1);
  pinMode(Player8LED, OUTPUT);

  if(playerNum == 1) {
    digitalWrite(Player1LED, 0);
  } 
  else if(playerNum == 2) {
    digitalWrite(Player2LED, 0);
  } 
  else if(playerNum == 3) {
    digitalWrite(Player3LED, 0);
  } 
  else if(playerNum == 4) {
    digitalWrite(Player4LED, 0);
  } 
  else if(playerNum == 5) {
    digitalWrite(Player5LED, 0);
  } 
  else if(playerNum == 6) {
    digitalWrite(Player6LED, 0);
  } 
  else if(playerNum == 7) {
    digitalWrite(Player7LED, 0);
  } 
  else if(playerNum == 8) {
    digitalWrite(Player8LED, 0);
  }
}

void enablePlayers(void) {
  pinMode(Player1LED, INPUT);
  pinMode(Player2LED, INPUT);
  pinMode(Player3LED, INPUT);
  pinMode(Player4LED, INPUT);
  pinMode(Player5LED, INPUT);
  pinMode(Player6LED, INPUT);
  pinMode(Player7LED, INPUT);
  pinMode(Player8LED, INPUT);
}


