#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2          // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;    // I2C

const int soilPin = A0;  // Soil moisture sensor analog pin
const int rainPin = 3;   // Rainfall sensor digital pin
LiquidCrystal_I2C lcd(0x27, 32, 4);  // Address, columns, rows

void setup() {
  Serial.begin(9600);
  dht.begin();
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Weather Station");
}

void loop() {
  // Read temperature and humidity from DHT sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Read temperature from BMP280 sensor
  float pressure = bmp.readPressure() / 100.0F; // Convert Pa to hPa

  // Read soil moisture
  int soilMoisture = analogRead(soilPin);

  // Read rainfall sensor
  int rainfall = digitalRead(rainPin);

  // Display readings on LCD
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");

  lcd.setCursor(0, 2);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print(" %");

  lcd.setCursor(0, 3);
  lcd.print("Pressure: ");
  lcd.print(pressure);
  lcd.print(" hPa");

  // Example for rainfall sensor LED indication
  if (rainfall == HIGH) {
    lcd.setCursor(16, 1);
    lcd.print("Rain: YES");
  } else {
    lcd.setCursor(16, 1);
    lcd.print("Rain: NO ");
  }

  delay(2000); // Delay between readings
}
