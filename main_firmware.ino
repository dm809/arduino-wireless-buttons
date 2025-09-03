/*
 * ОСНОВНАЯ ПРОШИВКА - Управление устройством через беспроводные рулевые кнопки
 * 
 * Подключение:
 * - Сигнальный провод от блока кнопок → Arduino A0
 * - GND от блока кнопок → Arduino GND  
 * - Arduino D2 → ULN2003 IN1 → OUT1 параллельно кнопке 1 устройства
 * - Arduino D3 → ULN2003 IN2 → OUT2 параллельно кнопке 2 устройства
 * - Arduino D4 → ULN2003 IN3 → OUT3 параллельно кнопке 3 устройства
 * 
 * Принцип работы: 
 * Arduino имитирует короткое нажатие кнопок устройства (100мс импульс)
 * Логика ВКЛ/ВЫКЛ определяется самим устройством
 * 
 * ВАЖНО: Перед использованием выполните калибровку проверочной прошивкой!
 * 
 * Автор: Твой канал
 */

const int remoteInput = A0;

// Выходы для управления через ULN2003
const int minus1 = 2;  // Кнопка 1
const int minus2 = 3;  // Кнопка 2
const int minus3 = 4;  // Кнопка 3

// Переменные для защиты от дребезга
unsigned long lastPress1 = 0;
unsigned long lastPress2 = 0;
unsigned long lastPress3 = 0;

void setup() {
  // Настройка выходов для ULN2003
  pinMode(minus1, OUTPUT);
  pinMode(minus2, OUTPUT);
  pinMode(minus3, OUTPUT);
  
  // Изначально все выходы выключены
  digitalWrite(minus1, LOW);
  digitalWrite(minus2, LOW);
  digitalWrite(minus3, LOW);
  
  Serial.begin(9600);
  Serial.println("===================================");
  Serial.println("  СИСТЕМА РУЛЕВЫХ КНОПОК ЗАПУЩЕНА ");
  Serial.println("===================================");
  Serial.println("Кнопка 1 (342) - Minus1 - Pin D2");
  Serial.println("Кнопка 2 (61)  - Minus2 - Pin D3");
  Serial.println("Кнопка 3 (164) - Minus3 - Pin D4");
  Serial.println("");
}

void loop() {
  int rawValue = analogRead(remoteInput);
  unsigned long currentTime = millis();
  
  // Кнопка 1 - rawValue 342 (диапазон 335-350)
  if (rawValue >= 335 && rawValue <= 350) {
    if (currentTime - lastPress1 > 300) {
      digitalWrite(minus1, HIGH);
      delay(100);  // Короткий импульс имитации нажатия
      digitalWrite(minus1, LOW);
      Serial.println(">>> Кнопка 1 нажата");
      lastPress1 = currentTime;
    }
  }
  
  // Кнопка 2 - rawValue 61 (диапазон 55-70)
  else if (rawValue >= 55 && rawValue <= 70) {
    if (currentTime - lastPress2 > 300) {
      digitalWrite(minus2, HIGH);
      delay(100);
      digitalWrite(minus2, LOW);
      Serial.println(">>> Кнопка 2 нажата");
      lastPress2 = currentTime;
    }
  }
  
  // Кнопка 3 - rawValue 164 (диапазон 155-170)
  else if (rawValue >= 155 && rawValue <= 170) {
    if (currentTime - lastPress3 > 300) {
      digitalWrite(minus3, HIGH);
      delay(100);
      digitalWrite(minus3, LOW);
      Serial.println(">>> Кнопка 3 нажата");
      lastPress3 = currentTime;
    }
  }
  
  delay(50);  // Небольшая задержка основного цикла
}

/*
 * НАСТРОЙКА ДИАПАЗОНОВ:
 * Если кнопки не срабатывают или срабатывают случайно - 
 * измените диапазоны значений согласно калибровочной прошивке
 * 
 * Пример настройки:
 * if (rawValue больше или равно МИНИМУМ и rawValue меньше или равно МАКСИМУМ)
 * 
 * СХЕМА ULN2003:
 * Arduino D2 к ULN2003 IN1, затем OUT1 к кнопке 1 устройства (параллельно)
 * Arduino D3 к ULN2003 IN2, затем OUT2 к кнопке 2 устройства (параллельно)  
 * Arduino D4 к ULN2003 IN3, затем OUT3 к кнопке 3 устройства (параллельно)
 * Arduino GND к ULN2003 GND
 */
