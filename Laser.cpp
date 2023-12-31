#define LASERPIN 11

String inputString = "APPLE";

const int ROW = 5;
const int COL = 8;

int binaryMatrix[ROW][COL];

void setup() {
  Serial.begin(9600);
  Serial.println("************Setup Initiated ...");
  pinMode(LASERPIN, OUTPUT);
  
  // Convert string to matrix of binary values
  for (int i = 0; i < ROW; i++) {
    char currentChar = inputString.charAt(i);

    // Convert character to 8-bit binary representation
    for (int j = COL - 1; j >= 0; j--) {
      binaryMatrix[i][j] = (currentChar >> (COL - 1 - j)) & 1;
    }
    
    for (int j = 0; j < 8; j++) {
      if (binaryMatrix[i][j] == 0) {
        binaryMatrix[i][j] = LOW;
      }
      else {
        binaryMatrix[i][j] = HIGH;
      }
    }
  }
}

int currentIndex = 0;

void loop() {
  if (currentIndex < ROW) {
    int bits[8];
    
    for (int i = 0; i < 8; i++) {
      bits[i] = binaryMatrix[currentIndex][i];
    }
    
    //start bit
    digitalWrite(LASERPIN, HIGH);
    
    delay(1000);
    
    digitalWrite(LASERPIN, LOW);
    
    for (int i = 0; i < 8; i++){
      //analogWrite(LASERPIN, bits[i]);
      if (bits[i] == LOW) {
        delay(1000);
      }
      else {
        digitalWrite(LASERPIN, HIGH);
        delay(1000);
        digitalWrite(LASERPIN, LOW);
      }
    }
    
    digitalWrite(LASERPIN, LOW);
    
    delay(1000);
    
    currentIndex++;
  }
}
