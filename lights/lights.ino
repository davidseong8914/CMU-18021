void setup() {
Serial.begin(9600);
pinMode(2, OUTPUT);
// pinMode(3, OUTPUT);
}

void loop() {

    // Code to turn on and off the lights

    // High Voltage
    Serial.println("Arduino now outputting High Voltage: 5V");
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, HIGH);
    delay(500);

    // Low Voltage
    Serial.println("Arduino now outputting Low Voltage: 3.3V");
    digitalWrite(2, LOW);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
}