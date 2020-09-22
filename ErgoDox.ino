/* -*- mode: c++ -*-
 * ErgoDox -- A very basic Kaleidoscope example for the ErgoDox
 * Copyright (C) 2018  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "Kaleidoscope.h"
#include <Kaleidoscope-Qukeys.h>
#include <Kaleidoscope-Macros.h>
#include <Kaleidoscope-LangPack-European.h>
#include <Kaleidoscope-Leader.h>
#include <Kaleidoscope-Unicode.h>

enum {
  QWERTY,
  SWERTY,
  SYMBOLS
};

using namespace kaleidoscope::language;

/* *INDENT-OFF* */
KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  (
      // left hand
      Key_Equals,            Key_1,         Key_2,     Key_3,         Key_4,   Key_5,   Key_LeftArrow,
      Key_Delete,            Key_Q,         Key_W,     Key_E,         Key_R,   Key_T,   LockLayer(SWERTY),
      Key_Backspace,         Key_A,         Key_S,     Key_D,         Key_F,   Key_G,
      Key_LeftShift,         CTL_T(Z),      Key_X,     Key_C,         Key_V,   Key_B,   LEAD(0),
      LT(SYMBOLS, Backtick), Key_Quote,     Key_NoKey, Key_LeftArrow, Key_RightArrow,

      Key_LeftAlt, Key_LeftGui,
      Key_Home,
      Key_Space, Key_Backspace, Key_End,

      // right hand
      Key_RightArrow,   Key_6,         Key_7,  Key_8,      Key_9,      Key_0,         Key_Minus,
      Key_NoKey,        Key_Y,         Key_U,  Key_I,      Key_O,      Key_P,         Key_Backslash,
                        Key_H,         Key_J,  Key_K,      Key_L,      Key_Semicolon, Key_Quote,
      Key_RightControl, Key_N,         Key_M,  Key_Comma,  Key_Period, CTL_T(Slash),  Key_RightShift,
      Key_UpArrow,      Key_DownArrow, Key_LeftBracket,    Key_RightBracket,          ___,

      Key_LeftAlt,  Key_Esc,
      Key_PageUp,
      Key_PageDown, Key_Tab, Key_Enter
  ),
  [SWERTY] = KEYMAP_STACKED
  (
      // left hand
      ___,       ___,     ___,   ___,         ___,     ___,         ___,
      ___,       ___,     ___,   ___,         ___,     ___,         UnlockLayer(SWERTY),
      ___,       ___,     ___,   ___,         ___,     ___,
      ___,       ___,     ___,   ___,         ___,     ___,         ___,
      ___,       ___,     ___,   ___,         ___,

      ___, ___,
      ___,
      ___, ___, ___,

      // right hand
      ___,       ___,     ___,  ___,          ___,      ___,           ___,
      ___,       ___,     ___,  ___,          ___,      ___,           INTL_ARING,
                 ___,     ___,  ___,          ___,      INTL_OUMLAUT,  INTL_AUMLAUT,
      ___,       ___,     ___,  ___,          ___,      ___,           ___,
                          ___,  ___,          ___,      ___,           ___,

      ___,  ___,
      ___,
      ___,  ___, ___
  ),
  [SYMBOLS] = KEYMAP_STACKED
  (
      // left hand
      Key_Escape, ___,     ___,   ___,         ___,     ___,                   ___,
      ___,        ___,     ___,   ___,         ___,     ___,                   UnlockLayer(SWERTY),
      ___,        ___,     ___,   ___,         ___,     ___,
      ___,        ___,     ___,   ___,         ___,     LSHIFT(Key_Backtick),  ___,
      ___,        ___,     ___,   ___,         ___,

      ___, ___,
      ___,
      ___, ___, ___,

      // right hand
      ___,       ___,                            ___,             ___,                                   ___,      ___,         ___,
      ___,       ___,                            ___,             ___,                                   ___,      ___,         ___,
                 Consumer_ScanPreviousTrack,     Key_VolumeDown,  Key_VolumeUp,  Consumer_ScanNextTrack, ___,      ___,
      ___,       ___,                            ___,             ___,                                   ___,      ___,         ___,
                                                 ___,             ___,                                   ___,      ___,         ___,

      ___,  ___,
      ___,
      ___,  ___, Consumer_PlaySlashPause
  )
)
/* *INDENT-ON* */
KALEIDOSCOPE_INIT_PLUGINS(Leader,
                          Qukeys,
                          Macros,
                          LangPack_EU,
                          Unicode
                          );
enum {
  LEAD_UNICODE_UCIS,
  LEAD_SHRUGGY,
};


static void Shruggy(uint8_t seqIndex) {
  ::Unicode.type(0xaf);
  ::Macros.play(MACRO(Tc(Backslash),
                      D(RightShift),
                      Tc(Minus),
                      Tc(9),
                      U(RightShift)));
  ::Unicode.type(0x30c4);
  ::Macros.play(MACRO(D(RightShift),
                      Tc(0),
                      Tc(Minus),
                      U(RightShift),
                      Tc(Slash)));
  ::Unicode.type(0xaf);
}
static const kaleidoscope::plugin::Leader::dictionary_t dictionary[] PROGMEM = LEADER_DICT
                          (
                           { LEADER_SEQ(LEAD(0), Key_S), Shruggy }
                           );

void setup() {
  // Qukeys.setTimeout(200);
  // Qukeys.setReleaseDelay(20);
  Kaleidoscope.setup();
  for (byte i = 1; i < 4; i++) {
    Kaleidoscope.device().setStatusLED(i, true);
    delay(250);
  }

  for (byte i = 3; i > 0; i--) {
    Kaleidoscope.device().setStatusLED(i, false);
    delay(250);
  }
  Leader.dictionary = dictionary;
  Kaleidoscope.device().debounce = 7;

  Qukeys.activate();
}

void loop() {
  Kaleidoscope.loop();
}
