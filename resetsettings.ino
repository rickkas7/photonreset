#include "Particle.h"

STARTUP(WiFi.selectAntenna(ANT_INTERNAL));

void setup() {
    EEPROM.clear();

    WiFi.useDynamicIP();
    WiFi.clearCredentials();

    // So you can tell the operations have completed
    pinMode(D7, OUTPUT);
    digitalWrite(D7, HIGH);
}

void loop() {
}
