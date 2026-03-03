#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize objects
Adafruit_MPU6050 mpu;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 if your scanner found a different address

void setup() {
  Serial.begin(115200);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("I2C Multi-Module");

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) { delay(10); }
  }
  
  lcd.setCursor(0, 1);
  lcd.print("MPU6050 Ready!");
  delay(2000);
  lcd.clear();
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Print to Serial Monitor
  Serial.print("Accel X: "); Serial.print(a.acceleration.x);
  Serial.print(", Y: "); Serial.print(a.acceleration.y);
  Serial.print(", Z: "); Serial.println(a.acceleration.z);

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("X: "); lcd.print(a.acceleration.x);
  
  lcd.setCursor(0, 1);
  lcd.print("Y: "); lcd.print(a.acceleration.y);

  delay(500); // 500ms refresh rate
}