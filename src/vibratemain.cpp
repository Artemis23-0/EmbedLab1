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

  cfg.external_speaker.atomic_spk = true;

  // Init device
  M5.begin();
  M5.Power.begin();
  M5.Speaker.begin();
  M5.Speaker.setVolume(244);

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
  M5.Speaker.tone(300 + ((passedProx + 1)* 10), 250 + (2000 - ((passedProx + 1) * 2)));
}

void vibrate(int passedProx) {
  int floor = 107;
  double divider = 3.5;

  if (passedProx > 100) {
    divider = 5;
  }
  M5.Power.setVibration(floor + ((passedProx + 1) / divider));
}