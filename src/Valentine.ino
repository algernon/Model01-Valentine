/* -*- mode: c++ -*-
 * Model01-Valentine - A Valentine's day gift
 * Copyright (C) 2017  Gergely Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Kaleidoscope.h>
#include <Kaleidoscope-LEDControl.h>
#include <Kaleidoscope-LED-AlphaSquare.h>
#include <Kaleidoscope-Macros.h>

const Key keymaps[][ROWS][COLS] PROGMEM = {
  [0] = KEYMAP_STACKED
  (
   Key_LEDEffectNext, Key_1, Key_2, Key_3, Key_4, Key_5, M(0),
   Key_Backtick,      Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_PageUp,        Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDn,        Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Esc,

   Key_LCtrl, Key_Backspace, Key_LGUI, Key_LShift,
   Key_skip,

   M(1),      Key_6, Key_7, Key_8,     Key_9,      Key_0,         Key_skip,
   Key_Enter, Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
              Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
   Key_skip,  Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,

   Key_RShift, Key_RAlt, Key_Space, Key_RCtrl,
   Key_skip
   ),
};

static void displayHeart (uint8_t redLevel) {
  static const uint16_t heartLeft =
    SYM4x4 (0, 0, 1, 0,
            0, 1, 1, 1,
            0, 1, 1, 1,
            0, 0, 0, 1);

  static const uint16_t heartRight =
    SYM4x4 (1, 0, 0, 0,
            1, 1, 0, 0,
            1, 1, 0, 0,
            0, 0, 0, 0);

  AlphaSquare.color = { 0x00, 0x00, redLevel };
  AlphaSquare.display (heartRight, 13);
  AlphaSquare.display (heartLeft, 9);
}

static void pulseHeart (void) {
  for (uint8_t i = 0x88; i > 0x22; i -= 0x4) {
    displayHeart (i);
    delay (10);
  }
  for (uint8_t i = 0x22; i <= 0x88; i += 0x4) {
    displayHeart (i);
  }
}

static void fadeChar (Key key) {
  for (uint8_t i = 0x88; i > 0x22; i -= 0x4) {
    displayHeart (i);
    delay (10);
  }
  for (uint8_t i = 0x00; i <= 0x88; i += 0x4) {
    AlphaSquare.color = { 0, 0, (uint8_t)min (i * 2, 255) };
    AlphaSquare.display (key);
    if (i >= 0x22)
      displayHeart (i);
  }

}

static void fadeOutChar (Key key) {
  for (uint8_t i = 0x88; i > 0x22; i -= 0x4) {
    displayHeart (i);
    AlphaSquare.color = { 0, 0, (uint8_t)min (i * 2, 255)};
    AlphaSquare.display (key);
    delay (10);
  }
  for (uint8_t i = 0x22; i >= 0x4; i -= 0x4) {
    AlphaSquare.color = { 0, 0, (uint8_t)min (i * 2, 255)};
    AlphaSquare.display (key);
  }
}

#define xCRGB(r, g, b) CRGB((uint8_t)(r), (uint8_t)(g), (uint8_t)(b))

static void fadePeach(float step) {
  // skirt
  for (uint8_t c = 2; c <= 5; c++) {
    LEDControl.led_set_crgb_at (3, c, xCRGB(250 * step, 123 * step, 226 * step));
  }
  LEDControl.led_set_crgb_at (2, 4, xCRGB(250 * step, 123 * step, 226 * step));
  LEDControl.led_set_crgb_at (2, 3, xCRGB(209 * step, 39 * step, 165 * step));

  // head
  LEDControl.led_set_crgb_at (1, 3, xCRGB(225 * step, 186 * step, 149 * step));

  // hair
  LEDControl.led_set_crgb_at (1, 4, xCRGB(255 * step, 255 * step, 0));
  LEDControl.led_set_crgb_at (0, 3, xCRGB(255 * step, 255 * step, 0));
  LEDControl.led_set_crgb_at (0, 4, xCRGB(255 * step, 255 * step, 0));
}

static void drawPeach(void) {
  for (uint8_t step = 0; step <= 100; step++) {
    fadePeach((float)step / 100.0);
    LEDControl.led_sync ();
  }
}

static void hidePeach(void) {
  for (uint8_t step = 100; step > 0; step--) {
    fadePeach((float)step / 100.0);
    LEDControl.led_sync ();
  }
  LEDControl.set_all_leds_to ({0, 0, 0});
  LEDControl.led_sync ();
}

static void fadeFlower(float step) {
  // middle
  LEDControl.led_set_crgb_at (2, 3, xCRGB(255 * step, 255 * step, 255 * step));

  // pinky
  LEDControl.led_set_crgb_at (2, 2, xCRGB(250 * step, 123 * step, 226 * step));
  LEDControl.led_set_crgb_at (2, 4, xCRGB(250 * step, 123 * step, 226 * step));
  LEDControl.led_set_crgb_at (1, 3, xCRGB(250 * step, 123 * step, 226 * step));
  LEDControl.led_set_crgb_at (3, 3, xCRGB(250 * step, 123 * step, 226 * step));

  // red
  LEDControl.led_set_crgb_at (0, 3, xCRGB(255 * step, 0, 0));
  LEDControl.led_set_crgb_at (1, 2, xCRGB(255 * step, 0, 0));
  LEDControl.led_set_crgb_at (1, 4, xCRGB(255 * step, 0, 0));
  LEDControl.led_set_crgb_at (2, 1, xCRGB(255 * step, 0, 0));
  LEDControl.led_set_crgb_at (2, 5, xCRGB(255 * step, 0, 0));
  LEDControl.led_set_crgb_at (3, 2, xCRGB(255 * step, 0, 0));
  LEDControl.led_set_crgb_at (3, 4, xCRGB(255 * step, 0, 0));
}

static void drawFlower(void) {
  for (uint8_t step = 0; step <= 100; step++) {
    fadeFlower((float)step / 100.0);
    LEDControl.led_sync ();
  }
}

static void hideFlower(void) {
  for (uint8_t step = 100; step > 0; step--) {
    fadeFlower((float)step / 100.0);
    LEDControl.led_sync ();
  }
  LEDControl.set_all_leds_to ({0, 0, 0});
  LEDControl.led_sync ();
}

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  if (!key_toggled_on (keyState))
    return MACRO_NONE;

  if (macroIndex == 0) {
    LEDControl.set_all_leds_to ({0, 0, 0});
    delay (100);

    // Initial beat
    for (uint8_t i = 0; i <= 0x88; i += 0x4) {
      displayHeart (i);
      delay (10);
    }

    pulseHeart ();

    // C
    fadeChar (Key_C);
    for (uint8_t i = 0; i < 4; i++) {
      pulseHeart ();
    }
    delay (500);
    fadeOutChar (Key_C);

    // [Transition]
    LEDControl.set_all_leds_to ({0, 0, 0});
    displayHeart (0x22);

    // S
    fadeChar (Key_S);
    for (uint8_t i = 0; i < 4; i++) {
      pulseHeart ();
    }
    delay (500);
    fadeOutChar (Key_S);

    // [Transition]
    LEDControl.set_all_leds_to ({0, 0, 0});
    displayHeart (0x22);

    // I
    fadeChar (Key_I);
    for (uint8_t i = 0; i < 4; i++) {
      pulseHeart ();
    }
    delay (500);
    fadeOutChar (Key_I);

    // [Transition]
    LEDControl.set_all_leds_to ({0, 0, 0});
    displayHeart (0x22);

    // L
    fadeChar (Key_L);
    for (uint8_t i = 0; i < 4; i++) {
      pulseHeart ();
    }
    delay (500);
    fadeOutChar (Key_L);

    // [Transition]
    LEDControl.set_all_leds_to ({0, 0, 0});
    displayHeart (0x22);

    // L
    fadeChar (Key_L);
    for (uint8_t i = 0; i < 4; i++) {
      pulseHeart ();
    }
    delay (500);
    fadeOutChar (Key_L);

    // [Transition]
    LEDControl.set_all_leds_to ({0, 0, 0});
    displayHeart (0x22);

    // A
    fadeChar (Key_A);
    for (uint8_t i = 0; i < 4; i++) {
      pulseHeart ();
    }
    delay (500);
    fadeOutChar (Key_A);

    // [Transition]
    LEDControl.set_all_leds_to ({0, 0, 0});
    displayHeart (0x22);

    // End Sequence
    for (uint8_t i = 0; i < 4; i++) {
      pulseHeart ();
    }

    for (uint8_t i = 0x88; i > 0x04; i -= 0x4) {
      displayHeart (i);
      delay (10);
    }

    LEDControl.set_all_leds_to ({0, 0, 0});
  }

  if (macroIndex == 1) {
    LEDControl.set_all_leds_to ({0, 0, 0});
    delay (100);

    // Initial beat
    for (uint8_t i = 0; i <= 0x88; i += 0x4) {
      displayHeart (i);
      delay (10);
    }

    // pulse
    pulseHeart ();

    // fade in peach
    drawPeach ();

    // pulse
    for (uint8_t i = 0; i < 8; i++) {
      pulseHeart ();
    }
    delay (500);

    // fade out peach
    hidePeach ();

    // transition
    pulseHeart();

    // fade in flower
    drawFlower();

    // pulse
    for (uint8_t i = 0; i < 8; i++) {
      pulseHeart ();
    }
    delay (500);

    hideFlower ();

    // End Sequence
    for (uint8_t i = 0; i < 4; i++) {
      pulseHeart ();
    }

    for (uint8_t i = 0x88; i > 0x04; i -= 0x4) {
      displayHeart (i);
      delay (10);
    }

    LEDControl.set_all_leds_to ({0, 0, 0});
  }

  return MACRO_NONE;
}

void setup () {
  Kaleidoscope.setup (KEYMAP_SIZE);

  Kaleidoscope.use (&LEDControl, &AlphaSquare, &Macros, NULL);
}

void loop () {
  Kaleidoscope.loop ();
}
