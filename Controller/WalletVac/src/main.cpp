#include <Arduino.h>


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

}

void loop() {
  // HIGH for 100ms
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(400);

  // HIGH for 100ms
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(400);

  // HIGH for 100ms
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(400);

  // HIGH for 100ms
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(400);

  delay(2000);

  // HIGH for 250ms
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);
  delay(250);

  // HIGH for 250ms
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);
  delay(250);

  // HIGH for 250ms
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);
  delay(250);

  // HIGH for 250ms
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);
  delay(250);

  delay(2000);
}

