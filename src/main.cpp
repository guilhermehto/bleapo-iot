#include <Arduino.h>
#include <BleapoBpm.h>

BleapoBpm bleapoBpm;

void setup() {
    Serial.begin(9600);
    bleapoBpm.Initialize(30000, 5, 20, 32);
}

void loop() {
    delay(20);

    bleapoBpm.Tick();
}