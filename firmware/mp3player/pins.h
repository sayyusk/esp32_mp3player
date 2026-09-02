// pins.h — every GPIO assignment for this project, in one place.
// Board: ESP32-WROVER. GPIO16/17 are reserved for PSRAM on this board —
// do not reuse them for anything, even if a tutorial elsewhere suggests it.
 
#ifndef PINS_H
#define PINS_H
 
// ---------------------------------------------------------
// Shared SPI bus — display, touch, and SD card all share
// these three lines. Only their CS pins differ.
// ---------------------------------------------------------
#define PIN_SPI_SCK   18
#define PIN_SPI_MISO  19
#define PIN_SPI_MOSI  23
 
// ---------------------------------------------------------
// Display (ILI9341)
// ---------------------------------------------------------
#define PIN_TFT_CS    5
#define PIN_TFT_DC    27   // moved from GPIO16 — reserved for PSRAM on WROVER
#define PIN_TFT_RST   0    // moved from GPIO17 — reserved for PSRAM on WROVER
                            // NOTE: GPIO0 is a boot-strap pin — needs a 10k pull-up to 3V3
#define PIN_TFT_LED   4    // backlight, doubles as screen on/off control
 
// ---------------------------------------------------------
// Touch controller (XPT2046) — not currently in use
// ---------------------------------------------------------
#define PIN_TOUCH_CS  15
 
// ---------------------------------------------------------
// microSD card
// ---------------------------------------------------------
#define PIN_SD_CS     13
// NOTE: this module also has an EN pin — tie it to 3V3 or the board
// may behave intermittently (see docs/circuit_plan.md for details)
 
// ---------------------------------------------------------
// I2S audio output -> PCM5102 DAC
// ---------------------------------------------------------
#define PIN_I2S_BCK   26
#define PIN_I2S_LRC   25
#define PIN_I2S_DOUT  2
 
// ---------------------------------------------------------
// Click wheel / encoder
// Currently wired to a temporary rotary encoder standing in
// for the real click wheel. Same pins will carry the real
// wheel's CLK/DATA lines once its full 8-pin mapping is
// confirmed (see docs/circuit_plan.md).
// ---------------------------------------------------------
#define PIN_WHEEL_CLK   32   // needs a 10k pull-up to 3V3 for the real click wheel
#define PIN_WHEEL_DATA  33
// PIN_WHEEL_CE / remaining click-wheel pins — TBD, pending verification
 
// ---------------------------------------------------------
// Buttons — all momentary, wired to GND when pressed unless noted.
// GPIO34/35/36/39 have NO internal pull-up hardware — external
// 10k resistors are mandatory on those, INPUT_PULLUP does nothing.
// ---------------------------------------------------------
#define PIN_BTN_POWER      39  // external 10k pull-up required
#define PIN_BATTERY_SENSE  36  // ADC input via voltage divider, not a button
 
#define PIN_BTN_VOL_UP     34  // external 10k pull-up required
#define PIN_BTN_VOL_DOWN   35  // external 10k pull-up required
 
#define PIN_BTN_SCREEN_TOGGLE 21  // internal INPUT_PULLUP is fine
#define PIN_BTN_SHUFFLE       22  // internal INPUT_PULLUP is fine
#define PIN_BTN_BACK           1  // TX0 — only usable once Serial isn't needed for debug
#define PIN_BTN_SELECT          3  // RX0 — center/click button
 
#define PIN_BTN_REPEAT     12  // WIRED OPPOSITE of the others — pull-DOWN, boot-strap pin.
                                 // Idles LOW, reads HIGH when pressed. Check for HIGH in code.
 
#endif // PINS_H
 