#include <SPI.h>
#include <MFRC522.h>

// Pin Definitions (Same as before)
#define SS_1_PIN  5   
#define RST_1_PIN 22  
#define SS_2_PIN  15  
#define RST_2_PIN 4   

MFRC522 mfrc522_1(SS_1_PIN, RST_1_PIN);
MFRC522 mfrc522_2(SS_2_PIN, RST_2_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Start SPI with a MUCH slower speed (1MHz instead of 4MHz or 10MHz)
  SPI.begin();
  
  // Initialize Reader 1
  Serial.println("Initializing Reader 1...");
  mfrc522_1.PCD_Init();
  delay(100); // Give it time to wake up
  mfrc522_1.PCD_DumpVersionToSerial();

  // Initialize Reader 2
  Serial.println("Initializing Reader 2...");
  mfrc522_2.PCD_Init();
  delay(100); 
  mfrc522_2.PCD_DumpVersionToSerial();

  Serial.println("\n--- Setup Complete ---");
}

void loop() {
  // Check Reader 1
  if (mfrc522_1.PICC_IsNewCardPresent() && mfrc522_1.PICC_ReadCardSerial()) {
    Serial.print("Reader 1 Scan: ");
    printHex(mfrc522_1.uid.uidByte, mfrc522_1.uid.size);
    mfrc522_1.PICC_HaltA();
    mfrc522_1.PCD_StopCrypto1(); // Stop communication to free up the bus
  }

  // Check Reader 2
  if (mfrc522_2.PICC_IsNewCardPresent() && mfrc522_2.PICC_ReadCardSerial()) {
    Serial.print("Reader 2 Scan: ");
    printHex(mfrc522_2.uid.uidByte, mfrc522_2.uid.size);
    mfrc522_2.PICC_HaltA();
    mfrc522_2.PCD_StopCrypto1();
  }
  
  delay(100); // Small pause to prevent bus congestion
}

void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
  Serial.println();
}