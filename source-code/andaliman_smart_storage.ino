#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_SHT31.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DS18B20
#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature ds18b20(&oneWire);

// SHT31
Adafruit_SHT31 sht31 = Adafruit_SHT31();

// Relay ACTIVE HIGH
#define RELAY_PELTIER 26      // IN1
#define RELAY_FAN_OUT 27      // IN2
#define RELAY_FAN_IN  14      // IN3

void setup() {

  Serial.begin(115200);

  Wire.begin(21, 22);

  // LCD
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Starting...");
  lcd.setCursor(0, 1);
  lcd.print("Please Wait");

  // DS18B20
  ds18b20.begin();

  // SHT31
  if (!sht31.begin(0x44)) {

    Serial.println("SHT31 ERROR");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SHT31 ERROR");

    while (1);
  }

  // Relay
  pinMode(RELAY_PELTIER, OUTPUT);
  pinMode(RELAY_FAN_OUT, OUTPUT);
  pinMode(RELAY_FAN_IN, OUTPUT);

  // Semua OFF saat startup
  digitalWrite(RELAY_PELTIER, LOW);
  digitalWrite(RELAY_FAN_OUT, LOW);
  digitalWrite(RELAY_FAN_IN, LOW);

  delay(2000);
  lcd.clear();

  Serial.println("================================");
  Serial.println(" SISTEM PENYIMPANAN ANDALIMAN ");
  Serial.println("================================");
}

void loop() {

  // =========================
  // Baca Sensor
  // =========================
  ds18b20.requestTemperatures();

  float suhuDS  = ds18b20.getTempCByIndex(0);
  float suhuSHT = sht31.readTemperature();
  float humSHT  = sht31.readHumidity();

  bool dsValid  = (suhuDS != DEVICE_DISCONNECTED_C);
  bool shtValid = !isnan(suhuSHT);

  // =========================
  // Pilih suhu kontrol
  // =========================
  float suhuKontrol;

  if (dsValid) {
    suhuKontrol = suhuDS;
  }
  else if (shtValid) {
    suhuKontrol = suhuSHT;
  }
  else {
    suhuKontrol = 99.0;
  }

  // =========================
  // LCD
  // =========================
  lcd.setCursor(0, 0);

  if (dsValid) {
    lcd.print("DS:");
    lcd.print(suhuDS, 1);
    lcd.print((char)223);
    lcd.print("C    ");
  } else {
    lcd.print("DS:ERROR      ");
  }

  lcd.setCursor(0, 1);

  if (shtValid) {
    lcd.print("S:");
    lcd.print(suhuSHT, 1);
    lcd.print(" H:");
    lcd.print(humSHT, 0);
    lcd.print("%   ");
  } else {
    lcd.print("SHT31 ERROR   ");
  }

  // =========================
  // Serial Monitor
  // =========================
  Serial.println("--------------------------------");

  Serial.print("DS18B20 : ");
  Serial.print(suhuDS);
  Serial.println(" C");

  Serial.print("SHT31   : ");
  Serial.print(suhuSHT);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humSHT);
  Serial.println(" %");

  // ===================================================
  // LOGIKA KONTROL FINAL
  // ===================================================

  // SUHU > 18°C
  if (suhuKontrol > 18.0)
  {
    digitalWrite(RELAY_PELTIER, HIGH);
    digitalWrite(RELAY_FAN_OUT, HIGH);
    digitalWrite(RELAY_FAN_IN, HIGH);

    Serial.println("SUHU > 18C");
    Serial.println("PELTIER ON");
    Serial.println("FAN LUAR ON");
    Serial.println("FAN DALAM ON");
  }

  // SUHU < 15°C
  else if (suhuKontrol < 15.0)
  {
    digitalWrite(RELAY_PELTIER, LOW);
    digitalWrite(RELAY_FAN_OUT, LOW);
    digitalWrite(RELAY_FAN_IN, HIGH);

    Serial.println("SUHU < 15C");
    Serial.println("PELTIER OFF");
    Serial.println("FAN LUAR OFF");
    Serial.println("FAN DALAM ON");
  }

  // SUHU 15°C - 18°C
  else
  {
    // RH 80 - 85 %
    if (humSHT >= 80.0 && humSHT <= 85.0)
    {
      digitalWrite(RELAY_PELTIER, HIGH);
      digitalWrite(RELAY_FAN_OUT, HIGH);
      digitalWrite(RELAY_FAN_IN, LOW);

      Serial.println("RH 80-85%");
      Serial.println("PELTIER ON");
      Serial.println("FAN LUAR ON");
      Serial.println("FAN DALAM OFF");
    }

    // RH >= 90 %
    else if (humSHT >= 90.0)
    {
      digitalWrite(RELAY_PELTIER, LOW);
      digitalWrite(RELAY_FAN_OUT, HIGH);
      digitalWrite(RELAY_FAN_IN, HIGH);

      Serial.println("RH >= 90%");
      Serial.println("PELTIER OFF");
      Serial.println("FAN LUAR ON");
      Serial.println("FAN DALAM ON");
    }

    // RH <80 atau RH 85-90
    else
    {
      digitalWrite(RELAY_PELTIER, HIGH);
      digitalWrite(RELAY_FAN_OUT, HIGH);
      digitalWrite(RELAY_FAN_IN, HIGH);

      Serial.println("RH BELUM SESUAI");
      Serial.println("PELTIER ON");
      Serial.println("FAN LUAR ON");
      Serial.println("FAN DALAM ON");
    }
  }

  delay(1000);
}