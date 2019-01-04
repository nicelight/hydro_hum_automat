/* Designed by Nicelight
        special for Oleg

    Олег, Тебе необходимо установить в сантиметрах
    уровень от ультразвукового датчика до дна ведра в строке 12
    Если захочешь изменить граничные значения температуры и влажности,
    можешь изменить их ниже в строках 15-19.
*/


// расстояние от ультразвукового датчика до дна ведра. Изменить под свое.
const float ultrasonic_to_ground_distance = 40.0;

// минимальная и максимальная температуры внутри бокса
float t_min = 24.0;
float t_max = 27.0;
// минимальная и максимальная влажность внутри бокса
float h_min = 40.0;
float h_max = 65.0;

// пины уз датчика
#define TRIG_PIN 16
#define ECHO_PIN 17

#define DHTPIN 14         // пин к которому подключен датчик DHT
// тип DHT датчика
#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

// для релюшек
//если включаются нулем
#define ON 0
#define OFF 1

#define RELAY1 24
#define RELAY2 26
#define UVLAJNITEL 28
#define OTTOK_AIR 30
#define PRITOK_AIR 32
#define RELAY6 34
#define RELAY7 36
#define RELAY8 38


/***************************************************************
 * ************************************************************/


#include <LiquidCrystal.h>
#include <Ultrasonic.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>

//#define DEBUG  // отладка

// пины для LCD экрана
#define RS 8
#define EN 9
#define D4 4
#define D5 5
#define D6 6
#define D7 7

// объявляем объект под уз датчик
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);
//объявляем объект под экранчик
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
// объявляем dht объект
DHT dht(DHTPIN, DHTTYPE);

float hum = 0; // влажность
float t_air = 0 ; // температура воздуха
long kompot_level  = 0; // уровень жидкости в баке, оперделяется уз датчиком
bool uvl_state = 0, pritok_state = 0, ottok_state = 0;
unsigned long ms = 0, airMs = 0, screenMs = 0, screenClrMs = 0, kompotMs = 0;
byte air = 0; // автомат  поддержки параметров воздуха
byte screen = 0; // автомат отрисовки экрана
byte kompot = 0; // автомат проверки уровня воды в баке


void setup() {
  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY1, OFF);
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY2, OFF);
  pinMode(UVLAJNITEL, OUTPUT);
  digitalWrite(UVLAJNITEL, OFF);
  pinMode(OTTOK_AIR, OUTPUT);
  digitalWrite(OTTOK_AIR, OFF);
  pinMode(PRITOK_AIR, OUTPUT);
  digitalWrite(PRITOK_AIR, OFF);
  pinMode(RELAY6, OUTPUT);
  digitalWrite(RELAY6, OFF);
  pinMode(RELAY7, OUTPUT);
  digitalWrite(RELAY7, OFF);
  pinMode(RELAY8, OUTPUT);
  digitalWrite(RELAY8, OFF);

  test_outs();

  Serial.begin(115200); // инициализация послед. порта
  while (!Serial);
  delay(10);
  dht.begin();
  delay(10);
  lcd.begin(16, 2);
  delay(10);
  lcd_intro();
  if ((t_min >= t_max) || (h_min >= h_max)) bad_settings_infinitly();
}//setup


void loop() {
  ms = millis();
  actions_handler();
  lcd_handler()

#ifdef DEBUG
  Serial.print("Hum: ");
  Serial.print(hum);
  Serial.print(" %");
  Serial.print("Temp: ");
  Serial.print(t_air);
  Serial.println(" C ");
#endif

}//loop
