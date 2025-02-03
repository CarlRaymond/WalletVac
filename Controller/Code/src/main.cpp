#include <Arduino.h>

uint16_t ONTIME_SHORT = 8;
uint16_t ONTIME_LONG = 50;

// Pin assignments
const int8_t PIN_LED_A = 2;     // IR LED1, active HIGH
const int8_t PIN_LED_B = 3;     // IR LED2, active HIGH
const int8_t PIN_LED_C = 4;     // IR LED3, active HIGH
const int8_t PIN_LED_D = 5;     // IR LED_D, active HIGH
const int8_t PIN_DET1 = 6;      // Detector 1, active LOW
const int8_t PIN_DET2 = 7;      // Detector 2, active LOW
const int8_t PIN_BELL = 13;     // Bell, active HIGH
const int8_t PIN_38KHz = 9;     // 38KHz

// Cycles 1 -> 2 -> 3 -> 4 at 400Hz
volatile int8_t activeLed = 1;

void setup() {

  // Configure Timer1 for 38,000Hz square wave on pin 9 (PortB 1)
  DDRB |= (1 << DDB1);    // Output on pin 9
  ICR1 = 420;             // Set top
  OCR1A = 105;            // Set compare
  
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

  // Set compare match register for 400Hz
  OCR2A = (16000000 / 1024) / 400 - 1; 

  // Enable Timer 2 output compare interrupt
  TIMSK2 |= (1 << OCIE2A);

  // Enable global interrupts
  sei(); 

  // Configure GPIO
  pinMode(PIN_BELL, OUTPUT);
  digitalWrite(PIN_BELL, LOW);
  pinMode(PIN_LED_A, OUTPUT);
  digitalWrite(PIN_LED_A, HIGH);
  pinMode(PIN_LED_B, OUTPUT);
  digitalWrite(PIN_LED_B, LOW);
  pinMode(PIN_LED_C, OUTPUT);
  digitalWrite(PIN_LED_C, LOW);
  pinMode(PIN_LED_D, OUTPUT);
  digitalWrite(PIN_LED_D, LOW);
  pinMode(PIN_DET1, INPUT);
  pinMode(PIN_DET2, INPUT);
}

// Invoked at 400Hz
ISR(TIMER2_COMPA_vect) {

  static volatile uint8_t ontime = 0;

  // Read detectors (Port D bits 6 and 7). If any activity, reset
  // the timeout counter.
  int8_t det = PIND & 0b11000000;
  if (det != 0b11000000) {
    ontime = 200;  // 0.5 seconds @ 400Hz
  }

  // Indicate output (Pin 13 = PORTB bit 5, active HIGH)
  if (ontime > 0) {
    PORTB |= (1 << 5);
    ontime--;
  }
  else {
    PORTB &= ~(1 << 5);
  }

  // LEDs on PORTD
  switch(activeLed) {
    case 1:
      // Bit 3 on, bit 2 off
      PORTD |= (1 << 3);
      PORTD &= ~(1 << 2);
      activeLed = 2;
      break;
    case 2:
      // Bit 4 on, bit 3 off
      PORTD |= (1 << 4);
      PORTD &= ~(1 << 3);
      activeLed = 3;
      break;
    case 3:
      // Bit 5 on, bit 4 off
      PORTD |= (1 << 5);
      PORTD &= ~(1 << 4);
      activeLed = 4;
      break;
    default:
      // Bit 2 on, bit 5 off
      PORTD |= (1 << 2);
      PORTD &= ~(1 << 5);
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

