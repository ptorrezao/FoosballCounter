#include "utils.h"
int teamAScore = 0, teamBScore = 0;

const int teamAButtonPin = D1;
const int teamBButtonPin = D2;
const int resetButtonPin = D3;
const int SIGNAL_PIR_PIN_TEAMA = D5;               
const int SIGNAL_PIR_PIN_TEAMB = D6;               
const int LED_PIN = D4;     

int lastTeamAState = 0;   
int lastTeamBState = 0;   

void resetCounters(){
  teamAScore =0;
  teamBScore =0;
}

void showResult(String aditionalMsg=""){

  String teamA = "Team A: "+ String(teamAScore);
  String teamB = "Team B: "+ String(teamBScore);

  Serial.println(teamA +" : "+teamB + " "+ aditionalMsg);
}

void AddTeamA(){

}
int button_Click(int buttonPin){
  int clickDetected = digitalRead(buttonPin);
  if (clickDetected == HIGH) {
      delay(250);
      blink();
      return 1;
  } 

  return 0;
}

void resetOn_Click(int buttonPin){
  int clickDetected = digitalRead(buttonPin);

  if (clickDetected == HIGH) {
      resetCounters();
      blink();
      showResult();
  } 
}

void scoreBoardEventsInit(){
  pinMode(teamAButtonPin, INPUT);
  pinMode(teamBButtonPin, INPUT);
  pinMode(resetButtonPin, INPUT);
  pinMode(SIGNAL_PIR_PIN_TEAMA, INPUT);
  pinMode(SIGNAL_PIR_PIN_TEAMB, INPUT);
  pinMode(LED_PIN, OUTPUT);

  resetCounters();
}

int checkMovement(int PIR_PIN, int lastState) 
{
  int state = digitalRead(PIR_PIN);
  if(state!=lastState) {
    lastState=state;
  
    if(state==HIGH) {
      while(digitalRead(PIR_PIN) == HIGH) {
         blink();
        delay(100);
      }
      
      return 1;
    }
    else
    {
      return 0;
    }
  } 

  return 0;
}

void scoreBoardEventsCheckClicks()
{
  resetOn_Click(resetButtonPin);

  int totalGoalsBeforeClick = teamAScore + teamBScore; 
  teamAScore += button_Click(teamAButtonPin);
  teamBScore += button_Click(teamBButtonPin);
  teamAScore+= checkMovement(SIGNAL_PIR_PIN_TEAMA,lastTeamAState);
  teamBScore+= checkMovement(SIGNAL_PIR_PIN_TEAMB,lastTeamBState);

  if (totalGoalsBeforeClick<(teamAScore+teamBScore))
  {
    showResult();
  }
  
}