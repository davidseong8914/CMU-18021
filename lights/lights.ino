void setup() {
Serial.begin(9600);
pinMode(2, OUTPUT);
// pinMode(3, OUTPUT);
}

void loop() {

    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, HIGH);
    delay(500);

    digitalWrite(2, LOW);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
}