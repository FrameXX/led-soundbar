#include <LEDSoundbar.h>

LEDSoundbar::LEDSoundbar(uint8_t dataPin, int LEDCount, CRGB minVolumeColor, CRGB maxVolumeColor) : LEDCount(LEDCount), minVolumeColor(minVolumeColor), maxVolumeColor(maxVolumeColor)
{
  this->LEDs = new CRGB[LEDCount];
  FastLED.addLeds<NEOPIXEL, 2>(this->LEDs, LEDCount);
}

LEDSoundbar::~LEDSoundbar()
{
  delete[] LEDs;
}

void LEDSoundbar::reportVolume(int volume)
{
  const CRGB enabledColor = this->getVolumeColor(volume);
  const int topEnabledLEDIndex = map(volume, 0, 1024, 0, this->LEDCount) - 1;

  if (topEnabledLEDIndex != -1)
  {
    for (int i = 0; i <= topEnabledLEDIndex; i++)
    {
      this->LEDs[i] = enabledColor;
    }
  }

  if (topEnabledLEDIndex != this->LEDCount - 1)
  {
    for (int i = topEnabledLEDIndex + 1; i <= this->LEDCount - 1; i++)
    {
      this->LEDs[i] = CRGB::Black;
    }
  }

  FastLED.show();
}

CRGB LEDSoundbar::getVolumeColor(int volume)
{
  const char r = map(volume, 0, 1024, this->minVolumeColor.r, this->minVolumeColor.r);
  const char g = map(volume, 0, 1024, this->minVolumeColor.g, this->minVolumeColor.g);
  const char b = map(volume, 0, 1024, this->minVolumeColor.b, this->minVolumeColor.b);
  return CRGB(r, g, b);
}