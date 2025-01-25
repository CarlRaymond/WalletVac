#include <Arduino.h>

uint16_t ONTIME_SHORT = 8;
uint16_t ONTIME_LONG = 50;

// Pin assignments
const int8_t PIN_BELL = 2;    // Bell, active LOW
const int8_t PIN_38KHz = 9;   // 38KHz
const int8_t PIN_LED1 = 10;   // IR LED1, active HIGH
const int8_t PIN_LED2 = 11;   // IR LED2, active HIGH
const int8_t PIN_LED3 = 12;   // IR LED3, active HIGH


// Cycles 1 -> 2 -> 3
volatile int8_t activeLed = 1;

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
  
  // Configure Timer2 to generate interrupt every 10ms (100 Hz)
  // CS22=1, CS21=1, CS20=1: Prescaler=1024
  // WGM22=0, WGM21=1, WGM20=0: CTC, use OCRA as TOP
  TCCR2A = (1 << WGM21);
  TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);

  // Set compare match register for 100Hz
  OCR2A = (16000000 / 1024) / 100 - 1; 

  // Enable Timer 2 output compare interrupt
  TIMSK2 |= (1 << OCIE2A);

  // Enable global interrupts
  sei(); 

  // Configure GPIO
  pinMode(PIN_BELL, OUTPUT);
  digitalWrite(PIN_BELL, HIGH);
  pinMode(PIN_LED1, OUTPUT);
  digitalWrite(PIN_LED1, LOW);
  pinMode(PIN_LED2, OUTPUT);
  digitalWrite(PIN_LED2, LOW);
  pinMode(PIN_LED3, OUTPUT);
  digitalWrite(PIN_LED3, LOW);
}

ISR(TIMER2_COMPA_vect) {
  switch(activeLed) {
    case 1:
      digitalWrite(PIN_LED1, LOW);
      digitalWrite(PIN_LED2, HIGH);
      activeLed = 2;
      break;
    case 2:
      digitalWrite(PIN_LED2, LOW);
      digitalWrite(PIN_LED3, HIGH);
      activeLed = 3;
      break;
    default:
      digitalWrite(PIN_LED3, LOW);
      digitalWrite(PIN_LED1, HIGH);
      activeLed = 1;
      break;
  }
}

void loop() {
  // Active for ONTIME
  digitalWrite(PIN_BELL, LOW);
  delay(ONTIME_SHORT);
  digitalWrite(PIN_BELL, HIGH);
  delay(200-ONTIME_SHORT);

  // Active for ONTIME
  digitalWrite(PIN_BELL, LOW);
  delay(ONTIME_SHORT);
  digitalWrite(PIN_BELL, HIGH);
  delay(200-ONTIME_SHORT);

  // HIGH for ONTIME
  digitalWrite(PIN_BELL, LOW);
  delay(ONTIME_SHORT);
  digitalWrite(PIN_BELL, HIGH);
  delay(200-ONTIME_SHORT);

  // HIGH for ONTIME
  digitalWrite(PIN_BELL, LOW);
  delay(ONTIME_SHORT);
  digitalWrite(PIN_BELL, HIGH);
  delay(200-ONTIME_SHORT);

  // HIGH for ONTIME
  digitalWrite(PIN_BELL, LOW);
  delay(ONTIME_SHORT);
  digitalWrite(PIN_BELL, HIGH);
  delay(200-ONTIME_SHORT);

  delay(2000);

  // HIGH for ONTIME_LONG
  digitalWrite(PIN_BELL, LOW);
  delay(ONTIME_LONG);
  digitalWrite(PIN_BELL, HIGH);
  delay(500-ONTIME_LONG);

  // HIGH for 250ms
  digitalWrite(PIN_BELL, LOW);
  delay(ONTIME_LONG);
  digitalWrite(PIN_BELL,HIGH);
  delay(500-ONTIME_LONG);

  // HIGH for 250ms
  digitalWrite(PIN_BELL, LOW);
  delay(ONTIME_LONG);
  digitalWrite(PIN_BELL, HIGH);
  delay(500-ONTIME_LONG);

  // HIGH for 250ms
  digitalWrite(PIN_BELL, LOW);
  delay(ONTIME_LONG);
  digitalWrite(PIN_BELL, HIGH);
  delay(500-ONTIME_LONG);

  delay(2000);
}

