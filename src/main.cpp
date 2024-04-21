#include <Arduino.h>
#include <FastLED.h>
#include <LEDSoundbar.h>
#include <Clamp.h>
#include <Amplify.h>
#include <CheapStepper.h>

#define LED_PIN1 3
#define LED_PIN2 4
#define NUM_LEDS1 17
#define NUM_LEDS2 33

#define MICROPHONE_PIN A1
#define MIN_VOLUME_VOLTAGE 44
#define MAX_VOLUME_VOLTAGE 62
#define VOLUME_AMPLIFY_EXPONENT 0.6

#define DELAY_MS 5

CRGB minVolumeColor(0, 255, 0);
CRGB maxVolumeColor(255, 0, 0);

LEDSoundbar<LED_PIN1> soundbar1(NUM_LEDS1, minVolumeColor, maxVolumeColor);
LEDSoundbar<LED_PIN2> soundbar2(NUM_LEDS2, minVolumeColor, maxVolumeColor);

CheapStepper stepper(8, 9, 10, 11);

int normalizeVolume(int volume, int minVolumeVoltage, int maxVolumeVoltage)
{
  volume = clamp(volume, minVolumeVoltage, maxVolumeVoltage);
  volume = map(volume, minVolumeVoltage, maxVolumeVoltage, 0, 1024);
  volume = amplify(volume, 0, 1024, VOLUME_AMPLIFY_EXPONENT);
  return volume;
}

void setup()
{
  Serial.begin(9600);

  stepper.setRpm(15);
  Serial.print(stepper.getRpm()); // get the RPM of the stepper
  Serial.print(" rpm = delay of ");
  Serial.print(stepper.getDelay()); // get delay between steps for set RPM
  Serial.print(" microseconds between steps");
  Serial.println();

  while (true)
  {
    const int microphoneVoltage = analogRead(MICROPHONE_PIN);
    const int volume = normalizeVolume(microphoneVoltage, MIN_VOLUME_VOLTAGE, MAX_VOLUME_VOLTAGE);
    soundbar1.reportVolume(volume);
    soundbar2.reportVolume(volume);

    stepper.moveDegrees(true, 360);
    delay(DELAY_MS);
  }
}

void loop()
{
}