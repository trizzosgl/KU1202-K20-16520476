#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);	// pin Arduino terhubung LCD
const int ping_Pin = A1;				// pin Arduino terhubung Ultrasonic sensor
long dur, cm;							// simpan nilai durasi dan jarak (cm)

void setup() {
  lcd.begin(16, 2);						// atur jumlah kolom dan baris LCD
  lcd.print("PING Sensor");
}

void loop() {
  cm = read_sensor_ultrasonic();
  
  /* Print to LCD */
  lcd.setCursor(0,1);					// atur kursor ke kolom 0 baris 1
  lcd.print("Jarak ");
  lcd.setCursor(6,1);					// atur kursor ke kolom 6 baris 1
  lcd.print(cm);						// cetak nilai jarak
  print_unit_cm(cm);					// cetak satuan (cm)
}

int read_sensor_ultrasonic() {
  pinMode(ping_Pin, OUTPUT);
  digitalWrite(ping_Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(ping_Pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping_Pin, LOW);
  
  pinMode(ping_Pin, INPUT);
  dur = pulseIn(ping_Pin, HIGH);
  cm = ms_to_cm(dur);
  
  if (cm >= 2 && cm <= 330){
    return cm;
  } else {
    return 0;
  }
}

long ms_to_cm(long ms) {
  return ms / 29 / 2;
}

void print_unit_cm(long cm){
  
  int ROW = 1;
  int ERR_Digit = 6;
  int oneDigit = 7;
  int twoDigit = 8;
  int threeDigit = 9;
  int lenUnit = 2;
  
  if (cm >= 2 && cm < 10){
    lcd.setCursor(oneDigit,ROW);
    lcd.print("cm");
    print_blank(oneDigit+lenUnit,ROW);
  } else if (cm >= 10 && cm < 100) {
    lcd.setCursor(twoDigit,ROW);
    lcd.print("cm");
    print_blank(threeDigit+lenUnit,ROW);
  } else {
    lcd.setCursor(ERR_Digit,ROW);
    print_blank(ERR_Digit,ROW);
  }
}

void print_blank(int col, int row){
  
  int total_col = 16;
  for (int i = col; i < total_col; i++){
    lcd.setCursor(1,row);
    lcd.print(" ");
  }
}