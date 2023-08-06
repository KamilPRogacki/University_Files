#include "DEV_Config.h"
#include "TSL2591.h"
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 10
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>

LiquidCrystal_PCF8574 lcd(0x27);
int sensor_A0 = A0;    // podłączenie od A0 na czujniku do A0 na Arduino
int sensor_D0 = 2;     // podłączenie od D0 na czujniku do pinu 2 na Arduino
int wartosc_A0;        // zmienna dla wartości A0
int wartosc_D0;        // zmienna dla wartości A0

UWORD Lux = 0;
const int watersensorPin= 2; //sensor pin connected to analog pin A2
int liquid_level;

void setup() {
 pinMode(2, INPUT);    // ustawienie pinu 2 jako wejście
 pinMode(5, OUTPUT);
 pinMode(watersensorPin, INPUT);//the liquid level sensor will be an input to the arduino
DEV_ModuleInit();
Serial.begin(115200);
Serial.print("TSL2591_Init\r\n");
TSL2591_Init();
Wire.begin();
Wire.beginTransmission(0x27);
lcd.begin(16, 2); // initialize the lcd
Lux = TSL2591_Read_Lux();
}

void loop() {
  wartosc_A0 = analogRead(sensor_A0);      // pobranie wartości z A0
  wartosc_D0 = digitalRead(sensor_D0);     // pobranie wartości z D0
  lcd.setBacklight(255);
  lcd.home();
  lcd.clear();
 //Serial.print("D0: ");                    // wyświetlenie na monitorze szeregowym
 //Serial.print(wartosc_D0);
  lcd.setCursor(0, 0);
  lcd.print("Wilgotnosc gleby:");
  lcd.setCursor(0, 1);
  lcd.print(wartosc_A0);
  delay(5000);  
  lcd.clear();
  DHT.read(DHT11_PIN);
  lcd.setCursor(0, 0);
  lcd.print("Temp powietrza:");
  lcd.setCursor(0, 1);
  lcd.print(DHT.temperature);
  lcd.setCursor(3, 1);
  lcd.print("st. C.");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  //Lux = TSL2591_Read_Lux();
  lcd.print("Poziom naswietlenia:");
  lcd.setCursor(0, 1);
  lcd.print(Lux);
  lcd.setCursor(6, 1);
  lcd.print("Lux");
  delay(5000);
  TSL2591_SET_LuxInterrupt(50,200);
  lcd.clear();
  DHT.read(DHT11_PIN);
  lcd.setCursor(0, 0);
  lcd.print("Wilg powietrza:");
  lcd.setCursor(0, 1);
  lcd.print(DHT.humidity);
  lcd.setCursor(3, 1);
  lcd.print("%");
  delay(5000);
  liquid_level= analogRead(watersensorPin); //arduino reads the value from the liquid level sensor
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Poziom wody:");
  lcd.setCursor(0, 1);
  lcd.print(liquid_level);
  delay(5000);
  if (wartosc_A0 < 900) {
  digitalWrite(5, HIGH);
  delay(5000);
  digitalWrite(5, LOW);
  delay(5000);
  }
    
  }
  
  
