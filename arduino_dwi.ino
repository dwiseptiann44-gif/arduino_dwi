const int ledPins[] = {7, 9, 10, 11}; // LED1–LED4
const int buttonStart = 2;
const int buttonStop = 3;
const int potPin = A0;

bool isActive = false;

void setup() {
  // Inisialisasi LED
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  // Inisialisasi tombol
  pinMode(buttonStart, INPUT_PULLUP);
  pinMode(buttonStop, INPUT_PULLUP);

  // Inisialisasi Serial Monitor
  Serial.begin(9600);
  Serial.println("Sistem Lampu Irama Musik Siap");
}

void loop() {
  // Baca tombol start
  if (digitalRead(buttonStart) == LOW) {
    isActive = true;
    Serial.println("Tombol START ditekan → Efek aktif");
    delay(200); // debounce
  }

  // Baca tombol stop
  if (digitalRead(buttonStop) == LOW) {
    isActive = false;
    Serial.println("Tombol STOP ditekan → Efek nonaktif, semua LED mati");
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    delay(200); // debounce
  }

  // Jika aktif, jalankan efek irama
  if (isActive) {
    int potValue = analogRead(potPin);
    int tempo = map(potValue, 0, 1023, 1000, 100); // Semakin tinggi, semakin cepat

    Serial.print("Potensiometer: ");
    Serial.print(potValue);
    Serial.print(" → Tempo: ");
    Serial.print(tempo);
    Serial.println(" ms");

    // Kedipan maju
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(tempo);
      digitalWrite(ledPins[i], LOW);
    }

    // Kedipan mundur (zigzag)
    for (int i = 3; i >= 0; i--) {
      digitalWrite(ledPins[i], HIGH);
      delay(tempo);
      digitalWrite(ledPins[i],LOW);
}
}
}