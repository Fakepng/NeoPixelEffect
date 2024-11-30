#ifndef LEDEFFECTS_H
#define LEDEFFECTS_H

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

/**
 * @class LEDEffects
 * @brief A class to control various LED effects on an Adafruit NeoPixel strip.
 */
class LEDEffects {
public:
  /**
   * @enum EffectType
   * @brief Enumeration of the different types of LED effects.
   */
  enum EffectType {
    NONE,        ///< No effect
    BLINK,       ///< Blink effect
    BREATH,      ///< Breath effect
    COLOR_WHEEL  ///< Color wheel effect
  };

  /**
   * @brief Constructor for the LEDEffects class.
   * @param strip Reference to the Adafruit NeoPixel strip.
   * @param pos The position of the LED in the strip to apply the effect to.
   */
  LEDEffects(Adafruit_NeoPixel& strip, uint16_t pos);

  /**
   * @brief Set the effect, color, and interval for the LED.
   * @param effect The type of effect to apply.
   * @param color The color of the effect.
   * @param interval The interval for the effect in milliseconds.
   */
  void set(EffectType effect, uint32_t color, uint16_t interval);

  /**
   * @brief Start the LED effect.
   */
  void start();

  /**
   * @brief Stop the LED effect.
   */
  void stop();

private:
  /**
   * @brief Task function to run the LED effect in a FreeRTOS task.
   * @param parameter Pointer to the LEDEffects object.
   */
  static void taskFunction(void* parameter);

  /**
   * @brief Update the LED effect.
   */
  void update();

  /**
   * @brief Generate a color from the color wheel.
   * @param wheelPos The position in the color wheel (0-255).
   * @return The color corresponding to the position in the color wheel.
   */
  uint32_t colorWheel(byte wheelPos);

  Adafruit_NeoPixel& strip;       ///< Reference to the Adafruit NeoPixel strip
  uint16_t ledPos;                ///< The position of the LED in the strip
  EffectType currentEffect;       ///< The current effect type
  uint32_t effectColor;           ///< The color of the effect
  uint16_t effectInterval;        ///< The interval for the effect in milliseconds
  bool effectRunning;             ///< Flag indicating if the effect is running
  uint32_t lastUpdate;            ///< The last update time for the effect
  float breathPhase;              ///< The phase for the breath effect
  uint8_t initialBrightness;      ///< The initial brightness of the LED
  float colorWheelPhase;          ///< The phase for the color wheel effect
  TaskHandle_t taskHandle;        ///< Handle for the FreeRTOS task
};

#endif