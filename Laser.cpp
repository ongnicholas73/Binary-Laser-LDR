// Define the pin connected to the laser
#define LASERPIN 11

// Define a string to be converted into a binary matrix
String inputString = "APPLE";

// Define the dimensions of the binary matrix
const int ROW = 5;
const int COL = 8;

// Declare a 2D array to store the binary representation of characters
int binaryMatrix[ROW][COL];

void setup() {
   // Initialize serial communication
  Serial.begin(9600);
  Serial.println("***** Setup Initiated *****");

  // Set the laser pin as an output
  pinMode(LASERPIN, OUTPUT);
  
  // Convert string to matrix of binary values
  for (int i = 0; i < ROW; i++) {
    char currentChar = inputString.charAt(i);

    // Convert character to 8-bit binary representation
    for (int j = COL - 1; j >= 0; j--) {
      binaryMatrix[i][j] = (currentChar >> (COL - 1 - j)) & 1;
    }
    
    // Map binary values to HIGH and LOW
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

// Initialize the index to traverse through the rows of the binary matrix
int currentIndex = 0;

void loop() {
  // Check if there are more rows to transmit
  if (currentIndex < ROW) {
    int bits[8];
    
    // Copy the bits of the current row to the bits array
    for (int i = 0; i < 8; i++) {
      bits[i] = binaryMatrix[currentIndex][i];
    }
    
    // Send Start Read Signal to Reciever
    digitalWrite(LASERPIN, HIGH);
    
    delay(1000);
    
    digitalWrite(LASERPIN, LOW);
    
    // Transmit the 8 data bits
    for (int i = 0; i < 8; i++){
      // Transmit a LOW bit with a delay
      if (bits[i] == LOW) {
        delay(1000);
      }
      else {
        // Transmit a HIGH bit with delays
        digitalWrite(LASERPIN, HIGH);
        delay(1000);
        digitalWrite(LASERPIN, LOW);
      }
    }
    
    // Ensure the laser is off after transmission
    digitalWrite(LASERPIN, LOW);
    
    // Delay before moving to the next row
    delay(1000);
    
    // Move to the next row in the binary matrix
    currentIndex++;
  }
}
