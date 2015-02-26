void setup() {
  Serial.begin(9600);
}

void loop() {
  listen();
}

void listen() {
  byte numEl;
  if (Serial.available()) {
    numEl = Serial.read();
    Serial.write(numEl);
  }
}
