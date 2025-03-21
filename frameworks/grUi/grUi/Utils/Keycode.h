// GroveEngine 2
// Copyright (C) 2020-2025 usernameak
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License, version 3, as
// published by the Free Software Foundation.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

enum class grKeycode {
    GR_KEY_UNKNOWN = 0x00,

    GR_KEY_BACK = 0x08,
    GR_KEY_TAB  = 0x09,

    GR_KEY_CLEAR  = 0x0C,
    GR_KEY_RETURN = 0x0D,

    GR_KEY_PAUSE   = 0x13,
    GR_KEY_CAPITAL = 0x14,

    GR_KEY_KANA = 0x15,

    GR_KEY_JUNJA = 0x17,
    GR_KEY_FINAL = 0x18,
    GR_KEY_KANJI = 0x19,

    GR_KEY_ESCAPE = 0x1B,

    GR_KEY_CONVERT    = 0x1C,
    GR_KEY_NONCONVERT = 0x1D,
    GR_KEY_ACCEPT     = 0x1E,
    GR_KEY_MODECHANGE = 0x1F,

    GR_KEY_SPACE    = 0x20,
    GR_KEY_PRIOR    = 0x21,
    GR_KEY_NEXT     = 0x22,
    GR_KEY_END      = 0x23,
    GR_KEY_HOME     = 0x24,
    GR_KEY_LEFT     = 0x25,
    GR_KEY_UP       = 0x26,
    GR_KEY_RIGHT    = 0x27,
    GR_KEY_DOWN     = 0x28,
    GR_KEY_SELECT   = 0x29,
    GR_KEY_PRINT    = 0x2A,
    GR_KEY_EXECUTE  = 0x2B,
    GR_KEY_SNAPSHOT = 0x2C,
    GR_KEY_INSERT   = 0x2D,
    GR_KEY_DELETE   = 0x2E,
    GR_KEY_HELP     = 0x2F,

    GR_KEY_0 = 0x30,
    GR_KEY_1 = 0x31,
    GR_KEY_2 = 0x32,
    GR_KEY_3 = 0x33,
    GR_KEY_4 = 0x34,
    GR_KEY_5 = 0x35,
    GR_KEY_6 = 0x36,
    GR_KEY_7 = 0x37,
    GR_KEY_8 = 0x38,
    GR_KEY_9 = 0x39,

    GR_KEY_A = 0x41,
    GR_KEY_B = 0x42,
    GR_KEY_C = 0x43,
    GR_KEY_D = 0x44,
    GR_KEY_E = 0x45,
    GR_KEY_F = 0x46,
    GR_KEY_G = 0x47,
    GR_KEY_H = 0x48,
    GR_KEY_I = 0x49,
    GR_KEY_J = 0x4A,
    GR_KEY_K = 0x4B,
    GR_KEY_L = 0x4C,
    GR_KEY_M = 0x4D,
    GR_KEY_N = 0x4E,
    GR_KEY_O = 0x4F,
    GR_KEY_P = 0x50,
    GR_KEY_Q = 0x51,
    GR_KEY_R = 0x52,
    GR_KEY_S = 0x53,
    GR_KEY_T = 0x54,
    GR_KEY_U = 0x55,
    GR_KEY_V = 0x56,
    GR_KEY_W = 0x57,
    GR_KEY_X = 0x58,
    GR_KEY_Y = 0x59,
    GR_KEY_Z = 0x5A,

    GR_KEY_LWIN = 0x5B,
    GR_KEY_RWIN = 0x5C,
    GR_KEY_APPS = 0x5D,

    GR_KEY_SLEEP = 0x5F,

    GR_KEY_NUMPAD0   = 0x60,
    GR_KEY_NUMPAD1   = 0x61,
    GR_KEY_NUMPAD2   = 0x62,
    GR_KEY_NUMPAD3   = 0x63,
    GR_KEY_NUMPAD4   = 0x64,
    GR_KEY_NUMPAD5   = 0x65,
    GR_KEY_NUMPAD6   = 0x66,
    GR_KEY_NUMPAD7   = 0x67,
    GR_KEY_NUMPAD8   = 0x68,
    GR_KEY_NUMPAD9   = 0x69,
    GR_KEY_MULTIPLY  = 0x6A,
    GR_KEY_ADD       = 0x6B,
    GR_KEY_SEPARATOR = 0x6C,
    GR_KEY_SUBTRACT  = 0x6D,
    GR_KEY_DECIMAL   = 0x6E,
    GR_KEY_DIVIDE    = 0x6F,
    GR_KEY_F1        = 0x70,
    GR_KEY_F2        = 0x71,
    GR_KEY_F3        = 0x72,
    GR_KEY_F4        = 0x73,
    GR_KEY_F5        = 0x74,
    GR_KEY_F6        = 0x75,
    GR_KEY_F7        = 0x76,
    GR_KEY_F8        = 0x77,
    GR_KEY_F9        = 0x78,
    GR_KEY_F10       = 0x79,
    GR_KEY_F11       = 0x7A,
    GR_KEY_F12       = 0x7B,
    GR_KEY_F13       = 0x7C,
    GR_KEY_F14       = 0x7D,
    GR_KEY_F15       = 0x7E,
    GR_KEY_F16       = 0x7F,
    GR_KEY_F17       = 0x80,
    GR_KEY_F18       = 0x81,
    GR_KEY_F19       = 0x82,
    GR_KEY_F20       = 0x83,
    GR_KEY_F21       = 0x84,
    GR_KEY_F22       = 0x85,
    GR_KEY_F23       = 0x86,
    GR_KEY_F24       = 0x87,

    GR_KEY_NUMLOCK = 0x90,
    GR_KEY_SCROLL  = 0x91,

    GR_KEY_OEM_FJ_JISHO   = 0x92, // 'Dictionary' key
    GR_KEY_OEM_FJ_MASSHOU = 0x93, // 'Unregister word' key
    GR_KEY_OEM_FJ_TOUROKU = 0x94, // 'Register word' key
    GR_KEY_OEM_FJ_LOYA    = 0x95, // 'Left OYAYUBI' key
    GR_KEY_OEM_FJ_ROYA    = 0x96, // 'Right OYAYUBI' key

    GR_KEY_LSHIFT   = 0xA0,
    GR_KEY_RSHIFT   = 0xA1,
    GR_KEY_LCONTROL = 0xA2,
    GR_KEY_RCONTROL = 0xA3,
    GR_KEY_LMENU    = 0xA4,
    GR_KEY_RMENU    = 0xA5,

    GR_KEY_BROWSER_BACK      = 0xA6,
    GR_KEY_BROWSER_FORWARD   = 0xA7,
    GR_KEY_BROWSER_REFRESH   = 0xA8,
    GR_KEY_BROWSER_STOP      = 0xA9,
    GR_KEY_BROWSER_SEARCH    = 0xAA,
    GR_KEY_BROWSER_FAVORITES = 0xAB,
    GR_KEY_BROWSER_HOME      = 0xAC,

    GR_KEY_VOLUME_MUTE         = 0xAD,
    GR_KEY_VOLUME_DOWN         = 0xAE,
    GR_KEY_VOLUME_UP           = 0xAF,
    GR_KEY_MEDIA_NEXT_TRACK    = 0xB0,
    GR_KEY_MEDIA_PREV_TRACK    = 0xB1,
    GR_KEY_MEDIA_STOP          = 0xB2,
    GR_KEY_MEDIA_PLAY_PAUSE    = 0xB3,
    GR_KEY_LAUNCH_MAIL         = 0xB4,
    GR_KEY_LAUNCH_MEDIA_SELECT = 0xB5,
    GR_KEY_LAUNCH_APP1         = 0xB6,
    GR_KEY_LAUNCH_APP2         = 0xB7,

    GR_KEY_OEM_1      = 0xBA, // ';:' for US
    GR_KEY_OEM_PLUS   = 0xBB, // '+' any country
    GR_KEY_OEM_COMMA  = 0xBC, // ',' any country
    GR_KEY_OEM_MINUS  = 0xBD, // '-' any country
    GR_KEY_OEM_PERIOD = 0xBE, // '.' any country
    GR_KEY_OEM_2      = 0xBF, // '/?' for US
    GR_KEY_OEM_3      = 0xC0, // '`~' for US
    GR_KEY_OEM_4      = 0xDB, //  '[{' for US
    GR_KEY_OEM_5      = 0xDC, //  '\|' for US
    GR_KEY_OEM_6      = 0xDD, //  ']}' for US
    GR_KEY_OEM_7      = 0xDE, //  ''"' for US
    GR_KEY_OEM_8      = 0xDF,

    GR_KEY_OEM_AX   = 0xE1, //  'AX' key on Japanese AX kbd
    GR_KEY_OEM_102  = 0xE2, //  "<>" or "\|" on RT 102-key kbd.
    GR_KEY_ICO_HELP = 0xE3, //  Help key on ICO
    GR_KEY_ICO_00   = 0xE4, //  00 key on ICO

    GR_KEY_PROCESSKEY = 0xE5,

    GR_KEY_ICO_CLEAR = 0xE6,

    GR_KEY_PACKET = 0xE7,

    GR_KEY_OEM_RESET   = 0xE9,
    GR_KEY_OEM_JUMP    = 0xEA,
    GR_KEY_OEM_PA1     = 0xEB,
    GR_KEY_OEM_PA2     = 0xEC,
    GR_KEY_OEM_PA3     = 0xED,
    GR_KEY_OEM_WSCTRL  = 0xEE,
    GR_KEY_OEM_CUSEL   = 0xEF,
    GR_KEY_OEM_ATTN    = 0xF0,
    GR_KEY_OEM_FINISH  = 0xF1,
    GR_KEY_OEM_COPY    = 0xF2,
    GR_KEY_OEM_AUTO    = 0xF3,
    GR_KEY_OEM_ENLW    = 0xF4,
    GR_KEY_OEM_BACKTAB = 0xF5,

    GR_KEY_ATTN      = 0xF6,
    GR_KEY_CRSEL     = 0xF7,
    GR_KEY_EXSEL     = 0xF8,
    GR_KEY_EREOF     = 0xF9,
    GR_KEY_PLAY      = 0xFA,
    GR_KEY_ZOOM      = 0xFB,
    GR_KEY_NONAME    = 0xFC,
    GR_KEY_PA1       = 0xFD,
    GR_KEY_OEM_CLEAR = 0xFE,

    GR_KEY_COUNT = 0x100
};