#define LDRPIN A0
#define THRESHOLD 10

int ambient = 0;

void setup() {
  pinMode(LDRPIN, INPUT);
  Serial.begin(9600);
  Serial.println("****setup inititated ...");
  
  ambient = analogRead(LDRPIN);
}

String charStr = "";

void loop() {
  int data = analogRead(LDRPIN);

  int bits[8];
  
  if (data > ambient + THRESHOLD) {
    delay(1000);
    
    for (int i = 0; i < 8; i++) {
      if (analogRead(LDRPIN) > ambient + THRESHOLD) {
        bits[i] = 1;
      }
      else {
        bits[i] = 0;
      }
      delay(1000);
    }
    
    // for (int i = 0; i < 8; i++) {
    //   Serial.print(bits[i]);
    // }
    
    String binaryString = "";
    
    for (int i = 0; i < 8; i++) {
      binaryString += String(bits[i]);
    }
    
    // Convert binary string to decimal number
    int decimalNumber = strtol(binaryString.c_str(), NULL, 2);
  
    // Convert decimal number to character
    char character = static_cast<char>(decimalNumber);
    
    charStr += character;
  
    // Print the result
    Serial.print("Binary: ");
    Serial.println(binaryString);
    Serial.print("Character: ");
    Serial.println(character);
  
    Serial.print("Secret Message: ");
    Serial.println(charStr);
  }
}
