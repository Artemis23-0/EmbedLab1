#include <Arduino.h>
#include <M5Unified.h>
#include <Adafruit_VCNL4040.h>

// put function declarations here:
void vibrate(int passedProx);
void speaker(int passedProx);

//Variables
Adafruit_VCNL4040 vcnl4040 = Adafruit_VCNL4040();
int freqSound = 0;
int freqVibration = 0;
uint16_t proximity = 1;



void setup() {
  auto cfg = M5.config();

  // If you want to play sound from ATOMIC Speaker, write this
  cfg.external_speaker.atomic_spk     = true;

  // Init device
  M5.begin();
  Serial.begin(115200);
  M5.Power.begin();
  M5.Speaker.begin();

  if (!vcnl4040.begin()) {
    Serial.println("Couldn't find VCNL4040 chip :(");
    while (1);
  }
  vcnl4040.setProximityHighResolution(false);
}

void loop() {
  M5.update();
  proximity = vcnl4040.getProximity();
  Serial.printf("Proximity: ");
  Serial.println(proximity);
  vibrate(proximity);
  speaker(proximity);
  delay(250);
}

void speaker(int passedProx) {
  M5.Speaker.setVolume(244);
  M5.Speaker.tone(300 + (passedProx * 10), 100 + (300 / ((passedProx + 1) * 10)));
}

void vibrate(int passedProx) {
  M5.Power.setVibration(300 + (passedProx * 10));
}