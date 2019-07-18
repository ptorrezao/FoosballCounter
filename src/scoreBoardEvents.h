int teamAScore = 0, teamBScore = 0;

const int teamAButtonPin = D1;
const int teamBButtonPin = D2;
const int resetButtonPin = D3;

void resetCounters(){
  teamAScore =0;
  teamBScore =0;
}

void showResult(){
  String teamA = "Team A: "+ String(teamAScore);
  String teamB = "Team B: "+ String(teamBScore);

  Serial.println(teamA +" : "+teamB);
}

int button_Click(int buttonPin, int score){
  int clickDetected = digitalRead(buttonPin);

  if (clickDetected == HIGH) {
      score+=1;
      showResult();
      delay(500);
  } 

  return score;
}

void resetOn_Click(int buttonPin){
  int clickDetected = digitalRead(buttonPin);

  if (clickDetected == HIGH) {
      resetCounters();
      showResult();
      delay(500);

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
  teamAScore = button_Click(teamAButtonPin,teamAScore);
  teamBScore = button_Click(teamBButtonPin,teamAScore);
  resetOn_Click(teamBButtonPin);
}