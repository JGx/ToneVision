#define WCLK_PIN 31
#define BCLK_PIN 33
#define LED 13
#define BITS_PER_SAMPLE 1

volatile int bit_count;

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  attachInterrupt(WCLK_PIN,word_isr,RISING);
  bit_count = 0;
}

void loop() {
  Serial.println(bit_count);
}

void word_isr(void) {
  digitalWrite(LED,HIGH);
  attachInterrupt(BCLK_PIN,bit_isr,RISING);
  detachInterrupt(WCLK_PIN);
}

void bit_isr(void) {
  bit_count++;
}
