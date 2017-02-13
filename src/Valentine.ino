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

   Key_skip,  Key_6, Key_7, Key_8,     Key_9,      Key_0,         Key_skip,
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

  return MACRO_NONE;
}

void setup () {
  Kaleidoscope.setup (KEYMAP_SIZE);

  Kaleidoscope.use (&LEDControl, &AlphaSquare, &Macros, NULL);
}

void loop () {
  Kaleidoscope.loop ();
}
