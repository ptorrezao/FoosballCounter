#include "utils.h"
int teamAScore = 0, teamBScore = 0;

const int teamAButtonPin = D1;
const int teamBButtonPin = D2;
const int resetButtonPin = D3;

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

  resetCounters();
}

void scoreBoardEventsCheckClicks()
{
  resetOn_Click(resetButtonPin);

  int totalGoalsBeforeClick = teamAScore + teamBScore; 
  teamAScore += button_Click(teamAButtonPin);
  teamBScore += button_Click(teamBButtonPin);

  if (totalGoalsBeforeClick<(teamAScore+teamBScore))
  {
    showResult();
  }
  
}