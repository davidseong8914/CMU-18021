
/*
 INPUT PINS
   2: controls VCC level (LOW for 5V or HIGH for 3V3)
   3: parallel (lo) or serial(hi)
   4: Input to first flip flop
   5: Clock signal
   6: Parallel control for A
   7: Parallel control for B
   + Powerlines and ground
 READ PINS
   A2: input A voltage
   A3: voltage after LED A’s pulldown resistor
   A4: voltage after LED A
   A5: VCC (either 5V or 3V3)
*/

// Pin Assignment
int control_VCC = 2;
int parallel = 3;
int dataPin = 4;    // Data input (first flip-flop input)
int clockPin = 5;   // Clock signal
int pinA = 6;       // Output A
int pinB = 7;       // Output B

// Read Pins (to measure voltages)
int pinVcc = A5;      // VCC (either 5V or 3V3)
int pinInputA = A0;   // Input A voltage
int pinResistorA = A3;// Voltage after LED A’s pulldown resistor
int pinAfterLED_A = A4;// Voltage after LED A

// A and B
int stateA = LOW;
int stateB = LOW;


void setup() {
Serial.begin(9600);

// Initialize
pinMode(control_VCC, OUTPUT);
pinMode(parallel, OUTPUT);

pinMode(dataPin, OUTPUT);  // data
pinMode(clockPin, OUTPUT); // clock
pinMode(pinA, OUTPUT);     // A
pinMode(pinB, OUTPUT);     // B

pinMode(pinVcc, INPUT); // VCC
pinMode(pinInputA, INPUT); // A Input Voltage
pinMode(pinResistorA, INPUT); // Voltage after LED A's pulldown resistor
pinMode(pinAfterLED_A, INPUT); // Voltage after LED A

digitalWrite(control_VCC, LOW);
digitalWrite(parallel, LOW);

digitalWrite(dataPin, LOW);
digitalWrite(clockPin, LOW);
digitalWrite(pinA, LOW);
digitalWrite(pinB, LOW);

}

void loop() {
  String message = "3.3V, Parallel";
  AB_states(400);
  V_reader(message);

  message = "5V, Parallel";
  digitalWrite(control_VCC, HIGH);
  AB_states(400);
  V_reader(message);

  message = "5V, Serial";
  digitalWrite(parallel, HIGH);
  AB_states(400);
  V_reader(message);

  message = "3.3V, Serial";
  digitalWrite(control_VCC, LOW);
  AB_states(400);
  V_reader(message);

  digitalWrite(parallel, LOW);
}

void AB_states(int Time) {
    // A B' | Set A High
  digitalWrite(clockPin, HIGH);
  digitalWrite(dataPin, HIGH);
  digitalWrite(clockPin, LOW);

  delay(Time);

  // A B | Set A High again, sets B high
  digitalWrite(clockPin, HIGH);
  digitalWrite(dataPin, HIGH);
  digitalWrite(clockPin, LOW);

  delay(Time);

  // A' B | Set A Low
  digitalWrite(clockPin, HIGH);
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);

  delay(Time);
  
  // A' B' | Set A Low again, sets B Low
  digitalWrite(clockPin, HIGH);
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);

  delay(Time);
}

void V_reader(String message) {
  int vcc = analogRead(pinVcc);
  int inputA = analogRead(pinInputA);
  int resistorA = analogRead(pinResistorA);
  int afterLED_A = analogRead(pinAfterLED_A);

  Serial.println();
  Serial.print("Voltage Readings for ");
  Serial.println(message);

  Serial.print("VCC: ");
  Serial.println(vcc * (5.0 / 1023.0), 3);  // Scale ADC value (0-1023) to voltage
  Serial.print("Input A voltage: ");
  Serial.println(inputA * (5.0 / 1023.0), 3);
  Serial.print("Voltage after LED A's pulldown resistor: ");
  Serial.println(resistorA * (5.0 / 1023.0), 3);
  Serial.print("Voltage after LED A: ");
  Serial.println(afterLED_A * (5.0 / 1023.0), 3);
}