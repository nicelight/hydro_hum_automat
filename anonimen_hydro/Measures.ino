void check_dht_sensor() { //
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  } else {
    hum = h;
    t_air = t;
  }
}//void check_dht_sensor()




void check_water_level_handler() {
  float try_dist = ultrasonic.Ranging(CM);
  // if bad measure - return
  if ((try_dist > 0) && (try_dist < (ultrasonic_to_ground_distance + 5.0))) {
    kompot_level = ultrasonic_to_ground_distance - try_dist;
  } else {
    Serial.print("Ultrasoniс Error. raw_dist = " ); 
    Serial.println(try_dist);
    return;
  }
}//void check_water_level_handler()


/*
  // Определение дистанции до объекта в см
  long getDistance() {
  long distacne_cm = getEchoTiming() * 1.71 * 0.01; //коеффициен пересчета, аналогичен делению на 58.4
  return distacne_cm;
  }
  // рассчет расстояния от жидкости  Определение времени задержки
  long getEchoTiming() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // генерируем импульс запуска
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // определение на пине echoPin длительности уровня HIGH, мксек:
  long duration = pulseIn(echoPin, HIGH);
  return duration;
  delay(100);
  }

  us.measure();
  dt = millis() - startTime;
  dt /= 1000;

  Serial.println(us.get_cm(), 3);
*/
