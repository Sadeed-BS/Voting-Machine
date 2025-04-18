const int buttonA = A0;
const int buttonB = A1;
const int buttonC = A2;
const int buttonD = A3;
const int closeButton = 3;
const int resultButton = 4;
const int resetButton = 5;
const int totalButton = 6;
const int ballotButton = 7;

int voteA = 0;
int voteB = 0;
int voteC = 0;
int voteD = 0;
bool closed = false;
bool ballotReady = false;

void setup() {
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonC, INPUT_PULLUP);
  pinMode(buttonD, INPUT_PULLUP);
  pinMode(closeButton, INPUT_PULLUP);
  pinMode(resultButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);
  pinMode(totalButton, INPUT_PULLUP);
  pinMode(ballotButton, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Voting Ready!");
  delay(1000);
}

void loop() {
  if (!closed) {
    if (digitalRead(ballotButton) == LOW) {
      ballotReady = true;
      Serial.println("Ballot Opened.");
      delay(300);
    }

    if (ballotReady && digitalRead(buttonA) == LOW) {
      voteA++;
      Serial.println("Vote Registered.");
      ballotReady = false;
      delay(300);
    }

    if (ballotReady && digitalRead(buttonB) == LOW) {
      voteB++;
      Serial.println("Vote Registered.");
      ballotReady = false;
      delay(300);
    }

    if (ballotReady && digitalRead(buttonC) == LOW) {
      voteC++;
      Serial.println("Vote Registered.");
      ballotReady = false;
      delay(300);
    }

    if (ballotReady && digitalRead(buttonD) == LOW) {
      voteD++;
      Serial.println("Vote Registered.");
      ballotReady = false;
      delay(300);
    }
  }

  if (digitalRead(closeButton) == LOW) {
    closed = true;
    Serial.println("Voting Closed!");
    delay(1000);
  }

  if (closed && digitalRead(resultButton) == LOW) {
    displayResults();
    delay(1000);
  }

  if (closed && digitalRead(totalButton) == LOW) {
    int totalVotes = voteA + voteB + voteC + voteD;
    Serial.print("Total Votes Registered: ");
    Serial.println(totalVotes);
    delay(500);
  }

  if (digitalRead(resetButton) == LOW) {
    voteA = voteB = voteC = voteD = 0;
    closed = false;
    ballotReady = false;
    Serial.println("Votes Reset!");
    delay(1000);
  }
}

void displayResults() {
  Serial.println("Results:");
  int totalVotes = voteA + voteB + voteC + voteD;
  if (totalVotes == 0) {
    Serial.println("No Votes Cast.");
    return;
  }

  Serial.print("BJP: "); Serial.println(voteA);
  Serial.print("INC: "); Serial.println(voteB);
  Serial.print("AAP: "); Serial.println(voteC);
  Serial.print("NOTA: "); Serial.println(voteD);

  if (voteA > voteB && voteA > voteC && voteA > voteD) {
    Serial.println("BJP Wins!");
  } else if (voteB > voteA && voteB > voteC && voteB > voteD) {
    Serial.println("INC Wins!");
  } else if (voteC > voteA && voteC > voteB && voteC > voteD) {
    Serial.println("AAP Wins!");
  } else if (voteD > voteA && voteD > voteB && voteD > voteC) {
    Serial.println("NOTA Wins!");
  } else {
    Serial.println("It's a Tie!");
  }
}