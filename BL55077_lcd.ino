#include <Wire.h>

// i2c
#define SCL_PIN 3
#define SDA_PIN 2
#define LCD_SAO 0b0
#define LCD_DRIVER_SUBADDR 0 << 2
#define LCD_DRIVER_ADDR 0b011111 << 2 | LCD_SAO << 1 | 0b0

// driver config
#define LCD_BIAS 0b0 // 0 = 1/3, 1 = 1/2
#define LCD_ENABLED 0b1
#define LCD_PWR_MODE 0b0 // 0 normal, 1 power-saving
#define BLINK_MODE 0b0 // 0 = normal blinking, 1 = alternate blinking

int cont = 0;
byte device_select_cmd = 0b0; // reset command
byte bank_select_cmd = 0b0;
byte display_data = 0b0;
byte current_bank = 0b0;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // display setup
  byte driver_config = 0 << 7 | 10 << 5 | LCD_PWR_MODE << 4 | LCD_ENABLED << 3 | LCD_BIAS << 2;
  Wire.beginTransmission(LCD_DRIVER_ADDR);
  Wire.write(driver_config);
  Wire.endTransmission();
}

void loop() {

  // build commands 
  byte device_select_cmd = 1 << 7 | 0b1100 << 3 | LCD_DRIVER_SUBADDR;  
  byte bank_select_cmd = 0 << 7 | 0b11110 << 2 | 00 << 1;
  byte display_data = 0b11111111;
   
  Wire.beginTransmission(LCD_DRIVER_ADDR);
  Wire.write(device_select_cmd);
  Wire.write(bank_select_cmd);
  Wire.write(display_data);
  Wire.endTransmission();
  delay(1);

}
