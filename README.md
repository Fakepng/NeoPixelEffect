# LEDEffects Library

The `LEDEffects` library provides a simple way to control various LED effects on an Adafruit NeoPixel strip. It supports effects such as blink, breath, and color wheel, and allows you to specify the position of the LED in the strip to apply the effect to.

## Features

- Blink effect
- Breath effect
- Color wheel effect
- Easy to use API
- Runs effects in the background using FreeRTOS tasks
- Supports specifying interval or cycle count for effects
- Automatically stops the effect after completing the specified number of cycles

## Installation

To install the `LEDEffects` library, copy the `LEDEffects.h` and `LEDEffects.cpp` files into your project's `lib` directory.

## Usage

### Include the Library

Include the `LEDEffects` library in your project:

```cpp
#include <Adafruit_NeoPixel.h>
#include "LEDEffects.h"
```

### Initialize the NeoPixel Strip and LEDEffects

Initialize the NeoPixel strip and the `LEDEffects` object:

```cpp
static const uint8_t LED_PIN = 8;
static const uint8_t LED_COUNT = 1;
static const uint8_t LED_BRIGHTNESS = 20;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
LEDEffects ledEffects(strip, 0); // Specify the LED position as 0
```

### Set and Start an Effect

Set and start an effect:

```cpp
void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(LED_BRIGHTNESS);

  // Set and start the blink effect
  ledEffects.set(LEDEffects::BLINK, strip.Color(255, 0, 0), 500); // Red color, 500ms interval
  ledEffects.start();
}
```

### Stop an Effect

Stop the effect:

```cpp
void loop() {
  // Stop the effect after some condition
  ledEffects.stop();
}
```

### Available Effects

- `LEDEffects::BLINK`: Blink effect
- `LEDEffects::BREATH`: Breath effect
- `LEDEffects::COLOR_WHEEL`: Color wheel effect

### Example

Here's a complete example:

```cpp
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "LEDEffects.h"

static const uint8_t LED_PIN = 8;
static const uint8_t LED_COUNT = 1;
static const uint8_t LED_BRIGHTNESS = 20;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
LEDEffects ledEffects(strip, 0); // Specify the LED position as 0

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(LED_BRIGHTNESS);

  // Set and start the blink effect with a cycle count
  ledEffects.set(LEDEffects::BLINK, strip.Color(255, 0, 0), 500, 10); // Red color, 500ms interval, 10 cycles
  ledEffects.start();

  // Wait for 5 seconds
  delay(5000);

  // Set and start the breath effect indefinitely
  ledEffects.set(LEDEffects::BREATH, strip.Color(0, 255, 0), 2000); // Green color, 2000ms interval
  ledEffects.start();

  // Wait for 5 seconds
  delay(5000);

  // Set and start the color wheel effect with a cycle count
  ledEffects.set(LEDEffects::COLOR_WHEEL, 0, 3000, 5); // Color wheel, 3000ms interval, 5 cycles
  ledEffects.start();
}

void loop() {
  // Your loop code here

  // Example to stop the effect after some condition
  // ledEffects.stop();
}
```

## API Reference

### `LEDEffects`

#### Constructor

```cpp
LEDEffects(Adafruit_NeoPixel& strip, uint16_t pos);
```

- `strip`: Reference to the Adafruit NeoPixel strip.
- `pos`: The position of the LED in the strip to apply the effect to.

#### `set`

```cpp
void set(EffectType effect, uint32_t color, uint16_t interval, uint16_t cycles = 0);
```

- `effect`: The type of effect to apply.
- `color`: The color of the effect.
- `interval`: The interval for the effect in milliseconds.
- `cycles`: The number of cycles for the effect (optional, default is 0 for infinite).

#### `start`

```cpp
void start();
```

Start the LED effect. This will cancel any previously running effect.

#### `stop`

```cpp
void stop();
```

Stop the LED effect.

## License

This library is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

## Version Changes

### v1.1.0

- Added support for specifying interval or cycle count for effects.
- Automatically stops the effect after completing the specified number of cycles.
- Ensured that calling `start` will cancel any previously running effect and start the new one.

### v1.0.0

- Initial release of the `LEDEffects` library.
- Features
  - Blink effect
  - Breath effect
  - Color wheel effect
  - Easy to use API
  - Runs effects in the background using FreeRTOS tasks
