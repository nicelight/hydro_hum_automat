void lcd_handler() {
  switch (screen) {
    case 0:
      screenMs = screenClrMs = ms;
      screen = 5;
      break;
    case 5:
      // раз в 10 сек подчищаем треш на всякий случай
      if ((ms - screenClrMs) > 10000) {
        screenClrMs = ms;
        lcd_clear();
      }//if 10000 ms
      // раз в пол секунды обновляем экран
      if ((ms - screenMs) > 500) {
        screenMs = ms;
        lcd.setCursor(0, 0);
        lcd.print("t=");
        lcd.print(t_air);
        lcd.print(" H=");
        lcd.print(hum);
        lcd.print(" w=");
        lcd.print(kompot_level);
        lcd.setCursor(0, 1);
        lcd.print("Air ");
        lcd_print_state(pritok_state);
        lcd.print(" Uvl ");
        lcd_print_state(uvl_state);
      }//if 500ms
      break;

  }//switch(screen)
}//void lcd_handler(){


// печатаем ON или OFF
void lcd_print_state(bool state) {
  if (state) {
    lcd.print(" ON");
  } else lcd.print("OFF");
}//void lcd_print_state()

// очищаем экран
void lcd_clear() {
  lcd.setCursor(0, 0);
  for (int i = 0; i < 16; i++) {
    lcd.print(" ");
  }
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    lcd.print(" ");
  }
}//void lcd_clear()


void lcd_intro() {
  lcd_clear();
  lcd.print(" --HYDROPONIC-- ");
  delay(500);
  lcd.setCursor(0, 1);  lcd.print("N"); delay(100);
  lcd.setCursor(1, 1);  lcd.print("i"); delay(100);
  lcd.setCursor(2, 1);  lcd.print("c"); delay(100);
  lcd.setCursor(3, 1);  lcd.print("e"); delay(100);
  lcd.setCursor(4, 1);  lcd.print("l"); delay(100);
  lcd.setCursor(5, 1);  lcd.print("i"); delay(100);
  lcd.setCursor(6, 1);  lcd.print("g"); delay(100);
  lcd.setCursor(7, 1);  lcd.print("h"); delay(100);
  lcd.setCursor(8, 1);  lcd.print("t"); delay(100);
  lcd.setCursor(9, 1);  lcd.print(" "); delay(100);
  lcd.setCursor(10, 1);  lcd.print("d"); delay(100);
  lcd.setCursor(11, 1);  lcd.print("e"); delay(100);
  lcd.setCursor(12, 1);  lcd.print("s"); delay(100);
  lcd.setCursor(13, 1);  lcd.print("i"); delay(100);
  lcd.setCursor(14, 1);  lcd.print("g"); delay(100);
  lcd.setCursor(15, 1);  lcd.print("n"); delay(500);
  lcd_clear();
}//void lcd_intro()

