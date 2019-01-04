void actions_handler() {
  switch (air) {
    case 0:
      airMs = ms;
      air = 5;
      break;
    // раз в секунду проверяем влажность и температуру воздуха
    case 5:
      if ((ms - airMs) > 1000) {
        airMs = ms;
        check_dht_sensor(); // производим замер параметров
        if (hum <= h_min) {
          uvl_state = 1; // состояние увлажнителя включено
          digitalWrite(UVLAJNITEL, ON);
        } else if (hum >= h_max) {
          uvl_state = 0; // состояние увлажнителя выкл
          digitalWrite(UVLAJNITEL, OFF);
        }//if hum
        if (t_air >= t_max) {
          pritok_state = 1;
          ottok_state = 1;
          digitalWrite(OTTOK_AIR, ON);
          digitalWrite(PRITOK_AIR, ON);
        } else if (t_air <= t_min) {
          pritok_state = 1;
          ottok_state = 1;
          digitalWrite(OTTOK_AIR, OFF);
          digitalWrite(PRITOK_AIR, OFF);
        }//if t_air
      }//if ms
      break;
  }//switch(air){

  switch (kompot) {
    case 0:
      kompotMs = ms;
      kompot = 5;
      break;
    // 10 раз в секунду мерим уровень
    case 5:
      if ((ms - kompotMs) > 500) {
        kompotMs = ms;
        // измерим расстояние до водицы
        check_water_level_handler();
      }//if ms
      break;
  }//switch(kompot)
}//void actions_handler()














void test_outs() {
  digitalWrite(RELAY1, ON);
  digitalWrite(RELAY2, ON);
  digitalWrite(UVLAJNITEL, ON);
  digitalWrite(OTTOK_AIR, ON);
  digitalWrite(PRITOK_AIR, ON);
  digitalWrite(RELAY6, ON);
  digitalWrite(RELAY7, ON);
  digitalWrite(RELAY8, ON);
  delay(1000);
  digitalWrite(RELAY1, OFF);
  digitalWrite(RELAY2, OFF);
  digitalWrite(UVLAJNITEL, OFF);
  digitalWrite(OTTOK_AIR, OFF);
  digitalWrite(PRITOK_AIR, OFF);
  digitalWrite(RELAY6, OFF);
  digitalWrite(RELAY7, OFF);
  digitalWrite(RELAY8, OFF);
  delay(500);
}//void test_outs()


void bad_settings_infinitly() {
  Serial.println("BAD SETTINGS");
  while (1) {
    digitalWrite(13, 1);
    delay(100);
    digitalWrite(13, 0);
    delay(100);
  }//while

}//void bad_settings_infinitly()
