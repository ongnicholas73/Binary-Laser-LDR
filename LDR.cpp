// Define the pin connected to the Analog Pin
#define LDRPIN A0 

// Define the threshold for detecting changes in light intensity
#define THRESHOLD 10

// Variable to store the ambient light level
int ambient = 0;

void setup() {
  // Set LDRPIN as input
  pinMode(LDRPIN, INPUT);

  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("***** Setup Inititated *****");
  
  // Read and store the ambient light level
  ambient = analogRead(LDRPIN);
}

// Variable to store characters received as binary
String charStr = "";

// Variables to measure processing time
unsigned long startTime;
unsigned long endTime;
unsigned long totalTime;

void loop() {
  // Read current light intensity from LDR
  int data = analogRead(LDRPIN);

  // Array to store binary bits
  int bits[8];
  
  // Check if the light intensity exceeds the ambient level plus the threshold
  if (data > ambient + THRESHOLD) {
     // Record the start time
    startTime = millis();
    
    // Introduce a delay for stability
    delay(1000);
    
    // Read 8 bits of data from the LDR
    for (int i = 0; i < 8; i++) {
      // Read 8 bits of data from the LDR
      if (analogRead(LDRPIN) > ambient + THRESHOLD) {
        bits[i] = 1;  // Set the bit to 1
      }
      else {
        bits[i] = 0;  // Set the bit to 0
      }
      // Introduce a delay for stability
      delay(1000);
    }
    
    // Record the end time
    endTime = millis();
    
    // Print the total processing time
    Serial.print("Total Processing Time (ms): ");
    Serial.println(endTime - startTime);
    
    // Update the total processing time
    totalTime += endTime - startTime;
    
    // Convert the array of bits to a binary string
    String binaryString = "";
    for (int i = 0; i < 8; i++) {
      binaryString += String(bits[i]);
    }
    
    // Convert binary string to decimal number
    int decimalNumber = strtol(binaryString.c_str(), NULL, 2);
  
    // Convert decimal number to character
    char character = static_cast<char>(decimalNumber);
    
    // Append the character to the charStr string
    charStr += character;
  
    // Print the binary representation of the received data
    Serial.print("Binary: ");
    Serial.println(binaryString);

    // Print the decoded character
    Serial.print("Character: ");
    Serial.println(character);
  
   // Print the total elapsed time
    Serial.print("Total Time Elapsed: ");
    Serial.println(totalTime);
    
    // Print the accumulated secret message
    Serial.print("Secret Message: ");
    Serial.println(charStr);
    
    // Print a newline for better readability
    Serial.println("");
  }
}
