#include <Arduino.h>
#include <FastLED.h>
#include <LEDSoundbar.h>
#include <Clamp.h>
#include <Amplify.h>

#define LED_PIN1 3
#define LED_PIN2 4
#define NUM_LEDS 16

#define MICROPHONE_PIN A0
#define MIN_VOLUME_VOLTAGE 32
#define MAX_VOLUME_VOLTAGE 64
#define VOLUME_AMPLIFY_EXPONENT 1

#define DELAY_MS 10

CRGB minVolumeColor(0, 255, 0);
CRGB maxVolumeColor(255, 0, 0);

LEDSoundbar<LED_PIN1> soundbar1(NUM_LEDS, minVolumeColor, maxVolumeColor);

int normalizeVolume(int volume, int minVolumeVoltage, int maxVolumeVoltage)
{
  volume = clamp(volume, minVolumeVoltage, maxVolumeVoltage);
  volume = map(volume, minVolumeVoltage, maxVolumeVoltage, 0, 1024);
  volume = amplify(volume, 0, 1024, VOLUME_AMPLIFY_EXPONENT);
  return volume;
}

void setup()
{
  while (true)
  {
    const int microphoneVoltage = analogRead(MICROPHONE_PIN);
    const int volume = normalizeVolume(microphoneVoltage, MIN_VOLUME_VOLTAGE, MAX_VOLUME_VOLTAGE);
    soundbar1.reportVolume(volume);
    delay(DELAY_MS);
  }
}

void loop()
{
}