// Main menu — using Adafruit_ILI9341 instead of TFT_eSPI.
// This library takes pins directly in code (no external config file to
// misconfigure), and it's already proven working on your exact wiring.

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS   5
#define TFT_DC   16
#define TFT_RST  17
#define TFT_LED  4

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// --- Encoder pins ---
#define ENC_CLK 32
#define ENC_DT  33

// --- Menu content ---
const char* mainMenuItems[] = { "Songs", "Playlists", "Artists", "Albums", "Pong", "Devices", "Settings" };
const int mainMenuCount = 7;
int selectedIndex = 2; // "Artists" selected, matching your HTML mockup

const int MENU_WIDTH = 190;
const int ITEM_HEIGHT = 32;
const int ITEM_RADIUS = 10;
const int HEADER_HEIGHT = 18;

int lastClk = HIGH;

// Colors (RGB triples 0-255, converted to 565 per-pixel as needed)
struct RGB { uint8_t r, g, b; };
RGB headerTop    = {0x24, 0x24, 0x24};
RGB headerBottom = {0x02, 0x02, 0x02};
RGB itemTop      = {0x2e, 0x2e, 0x2e};
RGB itemBottom   = {0x02, 0x02, 0x02};
RGB selectedTop    = {0xff, 0xff, 0xff};
RGB selectedBottom = {0xd6, 0xd6, 0xd6};
uint16_t COLOR_SIDEPANEL = 0x1082; // placeholder until wallpaper art goes here

RGB lerpRGB(RGB a, RGB b, float t) {
  RGB out;
  out.r = a.r + (b.r - a.r) * t;
  out.g = a.g + (b.g - a.g) * t;
  out.b = a.b + (b.b - a.b) * t;
  return out;
}

// ---------- Helpers ----------

// Rounded-right-corners-only gradient fill, single pass, true transparency
// on the corners (doesn't overpaint with a fixed background color, so it's
// safe once a wallpaper image goes behind this later).
void fillRoundRectRightOnlyGradient(int x, int y, int w, int h, int r, RGB top, RGB bottom) {
  for (int i = 0; i < h; i++) {
    float t = (float)i / (float)(h - 1);
    RGB c = lerpRGB(top, bottom, t);
    uint16_t rowColor = tft.color565(c.r, c.g, c.b);

    int cornerCut = 0;
    if (i < r) {
      int dy = r - i;
      int chordHalfWidth = (int)sqrt((float)(r * r) - (float)(dy * dy));
      cornerCut = r - chordHalfWidth;
    } else if (i >= h - r) {
      int dy = i - (h - r) + 1;
      int chordHalfWidth = (int)sqrt((float)(r * r) - (float)(dy * dy));
      cornerCut = r - chordHalfWidth;
    }

    tft.drawFastHLine(x, y + i, w - cornerCut, rowColor);
  }
}

// ---------- Drawing ----------

void drawHeader() {
  for (int i = 0; i < HEADER_HEIGHT; i++) {
    float t = (float)i / (float)(HEADER_HEIGHT - 1);
    RGB c = lerpRGB(headerTop, headerBottom, t);
    tft.drawFastHLine(0, i, tft.width(), tft.color565(c.r, c.g, c.b));
  }
  tft.drawFastHLine(0, HEADER_HEIGHT, tft.width(), ILI9341_BLACK);
  tft.drawFastHLine(0, HEADER_HEIGHT + 1, tft.width(), tft.color565(0x33, 0x33, 0x33));
  tft.drawFastHLine(0, HEADER_HEIGHT + 2, tft.width(), tft.color565(0x1a, 0x1a, 0x1a));

  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE, tft.color565(headerTop.r, headerTop.g, headerTop.b));
  tft.setCursor(7, HEADER_HEIGHT / 2 - 3);
  tft.print("9:30");

  tft.setCursor(tft.width() - 34, HEADER_HEIGHT / 2 - 3);
  tft.print("100%");
}

void drawSidePanel() {
  int panelX = MENU_WIDTH;
  int panelY = HEADER_HEIGHT + 3;
  int panelW = tft.width() - MENU_WIDTH;
... (79 lines left)