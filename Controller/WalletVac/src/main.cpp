#include <Arduino.h>

uint16_t ONTIME_SHORT = 8;
uint16_t ONTIME_LONG = 50;

void setup() {

  // Configure Timer1 for 38,000Hz square wave on pin 9 (PortB 1)
  DDRB |= (1 << DDB1);    // Output on pin 9
  ICR1 = 420;             // Set top
  OCR1A = 210;            // Set compare
  
  // Timer 1 mode bits:
  // CS12=0, CS11=0, CS10=1: Prescaler=1
  // WGM13=1, WGM12=1, WGM11=1, WGM10=0: Fast PWM, use ICR1 as TOP
  // COM1A1=1 COM1A0=0: Non-inverting mode
  TCCR1A = (1 << COM1A1) | (1 << WGM11);
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);
  
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

}

void loop() {
  // HIGH for ONTIME
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  delay(ONTIME_SHORT);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  delay(200-ONTIME_SHORT);

  // HIGH for ONTIME
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  delay(ONTIME_SHORT);
  digitalWrite(13, LOW);
  digitalWrite(12,HIGH);
  delay(200-ONTIME_SHORT);

  // HIGH for ONTIME
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  delay(ONTIME_SHORT);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  delay(200-ONTIME_SHORT);

  // HIGH for ONTIME
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  delay(ONTIME_SHORT);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  delay(200-ONTIME_SHORT);

  // HIGH for ONTIME
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  delay(ONTIME_SHORT);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  delay(200-ONTIME_SHORT);

  delay(2000);

  // HIGH for ONTIME_LONG
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  delay(ONTIME_LONG);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  delay(500-ONTIME_LONG);

  // HIGH for 250ms
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  delay(ONTIME_LONG);
  digitalWrite(13, LOW);
  digitalWrite(12,HIGH);
  delay(500-ONTIME_LONG);

  // HIGH for 250ms
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  delay(ONTIME_LONG);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  delay(500-ONTIME_LONG);

  // HIGH for 250ms
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  delay(ONTIME_LONG);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  delay(500-ONTIME_LONG);

  delay(2000);
}

