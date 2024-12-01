#include "LEDEffects.h"
#include <math.h>

LEDEffects::LEDEffects(Adafruit_NeoPixel& strip, uint16_t pos) : strip(strip), ledPos(pos), currentEffect(NONE), effectRunning(false), lastUpdate(0), breathPhase(0), taskHandle(NULL), colorWheelPhase(0), effectCycles(0), currentCycle(0) {
  initialBrightness = strip.getBrightness();
}

void LEDEffects::set(EffectType effect, uint32_t color, uint16_t interval, uint16_t cycles) {
  currentEffect = effect;
  effectColor = color;
  effectInterval = interval;
  effectCycles = cycles;
  currentCycle = 0;
  initialBrightness = strip.getBrightness();
}

void LEDEffects::start() {
  // Stop any running effect before starting a new one
  stop();

  effectRunning = true;
  xTaskCreatePinnedToCore(taskFunction, "LEDEffectsTask", 2048, this, 1, &taskHandle, 0);
}

void LEDEffects::stop() {
  if (taskHandle != NULL) {
    effectRunning = false;
    vTaskDelete(taskHandle);
    taskHandle = NULL;
    strip.setPixelColor(ledPos, 0);
    strip.show();
  }
}

void LEDEffects::taskFunction(void* parameter) {
  LEDEffects* ledEffects = static_cast<LEDEffects*>(parameter);
  while (ledEffects->effectRunning) {
    ledEffects->update();
    vTaskDelay(10 / portTICK_PERIOD_MS); // Adjust delay as needed
  }
}

void LEDEffects::update() {
  uint32_t currentTime = millis();
  uint16_t interval = effectCycles > 0 ? effectInterval / effectCycles : effectInterval;

  if (currentEffect == BLINK && currentTime - lastUpdate >= interval / 2) {
    uint32_t currentColor = strip.getPixelColor(ledPos);
    strip.setPixelColor(ledPos, currentColor == 0 ? effectColor : 0);
    strip.show();
    lastUpdate = currentTime;
    if (currentColor == 0) {
      currentCycle++;
      if (effectCycles > 0 && currentCycle >= effectCycles) {
        stop();
      }
    }
  }

  if (currentEffect == BREATH) {
    float phaseIncrement = (2 * PI) / (interval / 10.0);
    breathPhase += phaseIncrement;
    if (breathPhase >= 2 * PI) {
      breathPhase -= 2 * PI;
      currentCycle++;
      if (effectCycles > 0 && currentCycle >= effectCycles) {
        stop();
      }
    }
    float brightness = (sin(breathPhase) + 1) / 2; // Normalize to 0-1
    strip.setBrightness(brightness * initialBrightness);
    strip.setPixelColor(ledPos, effectColor);
    strip.show();
    lastUpdate = currentTime;
  }

  if (currentEffect == COLOR_WHEEL) {
    float phaseIncrement = 256.0 / (interval / 10.0);
    colorWheelPhase += phaseIncrement;
    if (colorWheelPhase >= 256) {
      colorWheelPhase -= 256;
      currentCycle++;
      if (effectCycles > 0 && currentCycle >= effectCycles) {
        stop();
      }
    }
    strip.setPixelColor(ledPos, colorWheel((byte)colorWheelPhase));
    strip.show();
    lastUpdate = currentTime;
  }
}

uint32_t LEDEffects::colorWheel(byte wheelPos) {
  wheelPos = 255 - wheelPos;
  if (wheelPos < 85) {
    return strip.Color(255 - wheelPos * 3, 0, wheelPos * 3);
  }
  if (wheelPos < 170) {
    wheelPos -= 85;
    return strip.Color(0, wheelPos * 3, 255 - wheelPos * 3);
  }
  wheelPos -= 170;
  return strip.Color(wheelPos * 3, 255 - wheelPos * 3, 0);
}