#pragma once

#include <Arduino.h>
#include <FastLED.h>

class LEDSoundbar
{
private:
  int LEDCount;
  CRGB minVolumeColor;
  CRGB maxVolumeColor;
  CRGB *LEDs;

  CRGB getVolumeColor(int volume);

public:
  LEDSoundbar(uint8_t dataPin, int LEDCount, CRGB minVolumeColor, CRGB maxVolumeColor);

  ~LEDSoundbar();

  void reportVolume(int volume);
};