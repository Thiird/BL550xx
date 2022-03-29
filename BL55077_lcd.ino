#include <Wire.h>

// i2c
#define SAO 0b0
#define DRIVER_SUBADDR 0 << 2
#define DRIVER_ADDR_77 0b00111000 // BL55077
#define DRIVER_ADDR_66 0b00111110 // BL55066

// driver config
#define BIAS 0b0 // 0 = 1/3, 1 = 1/2
#define ENABLED 0b1
#define PWR_MODE 0b0 // 0 normal, 1 power-saving
#define BLINK_MODE 0b0 // 0 = normal blinking, 1 = alternate blinking

byte driver_config = 0;
byte device_select_cmd = 0;
byte bank_select_cmd = 0;
byte display_data = 0b0;
byte current_bank = 0b0;
byte ram_addr = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("---------------");
  
  // display setup 0b0 << 7 | 0b10 << 5 | LCD_PWR_MODE << 4 | LCD_ENABLED << 3 | LCD_BIAS << 2 | 0b1;
  driver_config = 0b11001001;
  device_select_cmd = 0b11100000; //1 << 7 | 0b1100 << 3 | LCD_DRIVER_SUBADDR;
  bank_select_cmd = 1 << 7 | 0b11110 << 2 | 00 << 1;

  Wire.begin();
  
  Wire.beginTransmission(DRIVER_ADDR_66);
  Wire.write(driver_config);
  Wire.write(device_select_cmd);
  Wire.write(bank_select_cmd);
  Wire.endTransmission();
  Serial.println("Setup Done");
}

void loop() {

  // build commands
  display_data = 0b11111111;
   
  Wire.beginTransmission(DRIVER_ADDR_66);
  Wire.write(ram_addr);
  Wire.write(display_data);
  Wire.endTransmission();
  Serial.println("Sending data ");
  delay(500);

  if (ram_addr < 250){ram_addr++;}
  else { ram_addr = 0; }
}
