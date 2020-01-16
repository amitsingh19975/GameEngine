#if !defined(DK_KEY_CODE_HPP)
#define DK_KEY_CODE_HPP

#include "ostream"

namespace dk{
    enum KeyCode
    {
        DK_KEY_UNKNOWN = 0,
        DK_KEY_A = 4,
        DK_KEY_B = 5,
        DK_KEY_C = 6,
        DK_KEY_D = 7,
        DK_KEY_E = 8,
        DK_KEY_F = 9,
        DK_KEY_G = 10,
        DK_KEY_H = 11,
        DK_KEY_I = 12,
        DK_KEY_J = 13,
        DK_KEY_K = 14,
        DK_KEY_L = 15,
        DK_KEY_M = 16,
        DK_KEY_N = 17,
        DK_KEY_O = 18,
        DK_KEY_P = 19,
        DK_KEY_Q = 20,
        DK_KEY_R = 21,
        DK_KEY_S = 22,
        DK_KEY_T = 23,
        DK_KEY_U = 24,
        DK_KEY_V = 25,
        DK_KEY_W = 26,
        DK_KEY_X = 27,
        DK_KEY_Y = 28,
        DK_KEY_Z = 29,

        DK_KEY_1 = 30,
        DK_KEY_2 = 31,
        DK_KEY_3 = 32,
        DK_KEY_4 = 33,
        DK_KEY_5 = 34,
        DK_KEY_6 = 35,
        DK_KEY_7 = 36,
        DK_KEY_8 = 37,
        DK_KEY_9 = 38,
        DK_KEY_0 = 39,

        DK_KEY_RETURN = 40,
        DK_KEY_ESCAPE = 41,
        DK_KEY_BACKSPACE = 42,
        DK_KEY_TAB = 43,
        DK_KEY_SPACE = 44,

        DK_KEY_MINUS = 45,
        DK_KEY_EQUALS = 46,
        DK_KEY_LEFTBRACKET = 47,
        DK_KEY_RIGHTBRACKET = 48,
        DK_KEY_BACKSLASH = 49, 
        DK_KEY_NONUSHASH = 50, 
        DK_KEY_SEMICOLON = 51,
        DK_KEY_APOSTROPHE = 52,
        DK_KEY_GRAVE = 53, 
        DK_KEY_COMMA = 54,
        DK_KEY_PERIOD = 55,
        DK_KEY_SLASH = 56,

        DK_KEY_CAPSLOCK = 57,

        DK_KEY_F1 = 58,
        DK_KEY_F2 = 59,
        DK_KEY_F3 = 60,
        DK_KEY_F4 = 61,
        DK_KEY_F5 = 62,
        DK_KEY_F6 = 63,
        DK_KEY_F7 = 64,
        DK_KEY_F8 = 65,
        DK_KEY_F9 = 66,
        DK_KEY_F10 = 67,
        DK_KEY_F11 = 68,
        DK_KEY_F12 = 69,

        DK_KEY_PRINTSCREEN = 70,
        DK_KEY_SCROLLLOCK = 71,
        DK_KEY_PAUSE = 72,
        DK_KEY_INSERT = 73, 
        DK_KEY_HOME = 74,
        DK_KEY_PAGEUP = 75,
        DK_KEY_DELETE = 76,
        DK_KEY_END = 77,
        DK_KEY_PAGEDOWN = 78,
        DK_KEY_RIGHT = 79,
        DK_KEY_LEFT = 80,
        DK_KEY_DOWN = 81,
        DK_KEY_UP = 82,

        DK_KEY_NUMLOCKCLEAR = 83, 
        DK_KEY_KP_DIVIDE = 84,
        DK_KEY_KP_MULTIPLY = 85,
        DK_KEY_KP_MINUS = 86,
        DK_KEY_KP_PLUS = 87,
        DK_KEY_KP_ENTER = 88,
        DK_KEY_KP_1 = 89,
        DK_KEY_KP_2 = 90,
        DK_KEY_KP_3 = 91,
        DK_KEY_KP_4 = 92,
        DK_KEY_KP_5 = 93,
        DK_KEY_KP_6 = 94,
        DK_KEY_KP_7 = 95,
        DK_KEY_KP_8 = 96,
        DK_KEY_KP_9 = 97,
        DK_KEY_KP_0 = 98,
        DK_KEY_KP_PERIOD = 99,

        DK_KEY_NONUSBACKSLASH = 100, 
        DK_KEY_APPLICATION = 101,
        DK_KEY_POWER = 102, 
        DK_KEY_KP_EQUALS = 103,
        DK_KEY_F13 = 104,
        DK_KEY_F14 = 105,
        DK_KEY_F15 = 106,
        DK_KEY_F16 = 107,
        DK_KEY_F17 = 108,
        DK_KEY_F18 = 109,
        DK_KEY_F19 = 110,
        DK_KEY_F20 = 111,
        DK_KEY_F21 = 112,
        DK_KEY_F22 = 113,
        DK_KEY_F23 = 114,
        DK_KEY_F24 = 115,
        DK_KEY_EXECUTE = 116,
        DK_KEY_HELP = 117,
        DK_KEY_MENU = 118,
        DK_KEY_SELECT = 119,
        DK_KEY_STOP = 120,
        DK_KEY_AGAIN = 121,
        DK_KEY_UNDO = 122,
        DK_KEY_CUT = 123,
        DK_KEY_COPY = 124,
        DK_KEY_PASTE = 125,
        DK_KEY_FIND = 126,
        DK_KEY_MUTE = 127,
        DK_KEY_VOLUMEUP = 128,
        DK_KEY_VOLUMEDOWN = 129,
        DK_KEY_KP_COMMA = 133,
        DK_KEY_KP_EQUALSAS400 = 134,

        DK_KEY_INTERNATIONAL1 = 135,
        DK_KEY_INTERNATIONAL2 = 136,
        DK_KEY_INTERNATIONAL3 = 137,
        DK_KEY_INTERNATIONAL4 = 138,
        DK_KEY_INTERNATIONAL5 = 139,
        DK_KEY_INTERNATIONAL6 = 140,
        DK_KEY_INTERNATIONAL7 = 141,
        DK_KEY_INTERNATIONAL8 = 142,
        DK_KEY_INTERNATIONAL9 = 143,
        DK_KEY_LANG1 = 144,
        DK_KEY_LANG2 = 145,
        DK_KEY_LANG3 = 146,
        DK_KEY_LANG4 = 147,
        DK_KEY_LANG5 = 148,
        DK_KEY_LANG6 = 149,
        DK_KEY_LANG7 = 150,
        DK_KEY_LANG8 = 151,
        DK_KEY_LANG9 = 152,

        DK_KEY_ALTERASE = 153,
        DK_KEY_SYSREQ = 154,
        DK_KEY_CANCEL = 155,
        DK_KEY_CLEAR = 156,
        DK_KEY_PRIOR = 157,
        DK_KEY_RETURN2 = 158,
        DK_KEY_SEPARATOR = 159,
        DK_KEY_OUT = 160,
        DK_KEY_OPER = 161,
        DK_KEY_CLEARAGAIN = 162,
        DK_KEY_CRSEL = 163,
        DK_KEY_EXSEL = 164,

        DK_KEY_KP_00 = 176,
        DK_KEY_KP_000 = 177,
        DK_KEY_THOUSANDSSEPARATOR = 178,
        DK_KEY_DECIMALSEPARATOR = 179,
        DK_KEY_CURRENCYUNIT = 180,
        DK_KEY_CURRENCYSUBUNIT = 181,
        DK_KEY_KP_LEFTPAREN = 182,
        DK_KEY_KP_RIGHTPAREN = 183,
        DK_KEY_KP_LEFTBRACE = 184,
        DK_KEY_KP_RIGHTBRACE = 185,
        DK_KEY_KP_TAB = 186,
        DK_KEY_KP_BACKSPACE = 187,
        DK_KEY_KP_A = 188,
        DK_KEY_KP_B = 189,
        DK_KEY_KP_C = 190,
        DK_KEY_KP_D = 191,
        DK_KEY_KP_E = 192,
        DK_KEY_KP_F = 193,
        DK_KEY_KP_XOR = 194,
        DK_KEY_KP_POWER = 195,
        DK_KEY_KP_PERCENT = 196,
        DK_KEY_KP_LESS = 197,
        DK_KEY_KP_GREATER = 198,
        DK_KEY_KP_AMPERSAND = 199,
        DK_KEY_KP_DBLAMPERSAND = 200,
        DK_KEY_KP_VERTICALBAR = 201,
        DK_KEY_KP_DBLVERTICALBAR = 202,
        DK_KEY_KP_COLON = 203,
        DK_KEY_KP_HASH = 204,
        DK_KEY_KP_SPACE = 205,
        DK_KEY_KP_AT = 206,
        DK_KEY_KP_EXCLAM = 207,
        DK_KEY_KP_MEMSTORE = 208,
        DK_KEY_KP_MEMRECALL = 209,
        DK_KEY_KP_MEMCLEAR = 210,
        DK_KEY_KP_MEMADD = 211,
        DK_KEY_KP_MEMSUBTRACT = 212,
        DK_KEY_KP_MEMMULTIPLY = 213,
        DK_KEY_KP_MEMDIVIDE = 214,
        DK_KEY_KP_PLUSMINUS = 215,
        DK_KEY_KP_CLEAR = 216,
        DK_KEY_KP_CLEARENTRY = 217,
        DK_KEY_KP_BINARY = 218,
        DK_KEY_KP_OCTAL = 219,
        DK_KEY_KP_DECIMAL = 220,
        DK_KEY_KP_HEXADECIMAL = 221,

        DK_KEY_LCTRL = 224,
        DK_KEY_LSHIFT = 225,
        DK_KEY_LALT = 226,
        DK_KEY_LGUI = 227,
        DK_KEY_RCTRL = 228,
        DK_KEY_RSHIFT = 229,
        DK_KEY_RALT = 230,
        DK_KEY_RGUI = 231,

        DK_KEY_MODE = 257,
                                
                                
        DK_KEY_AUDIONEXT = 258,
        DK_KEY_AUDIOPREV = 259,
        DK_KEY_AUDIOSTOP = 260,
        DK_KEY_AUDIOPLAY = 261,
        DK_KEY_AUDIOMUTE = 262,
        DK_KEY_MEDIASELECT = 263,
        DK_KEY_WWW = 264,
        DK_KEY_MAIL = 265,
        DK_KEY_CALCULATOR = 266,
        DK_KEY_COMPUTER = 267,
        DK_KEY_AC_SEARCH = 268,
        DK_KEY_AC_HOME = 269,
        DK_KEY_AC_BACK = 270,
        DK_KEY_AC_FORWARD = 271,
        DK_KEY_AC_STOP = 272,
        DK_KEY_AC_REFRESH = 273,
        DK_KEY_AC_BOOKMARKS = 274,


        DK_KEY_BRIGHTNESSDOWN = 275,
        DK_KEY_BRIGHTNESSUP = 276,
        DK_KEY_DISPLAYSWITCH = 277,
                                        
        DK_KEY_KBDILLUMTOGGLE = 278,
        DK_KEY_KBDILLUMDOWN = 279,
        DK_KEY_KBDILLUMUP = 280,
        DK_KEY_EJECT = 281,
        DK_KEY_SLEEP = 282,

        DK_KEY_APP1 = 283,
        DK_KEY_APP2 = 284,


        DK_KEY_AUDIOREWIND = 285,
        DK_KEY_AUDIOFASTFORWARD = 286,

    
        DK_NUM_KEY = 512 

    };

    static char const* KeyCodeToString[] = {
        "UNKNOWN" ,
        "A" ,
        "B" ,
        "C" ,
        "D" ,
        "E" ,
        "F" ,
        "G" ,
        "H" ,
        "I" ,
        "J" ,
        "K" ,
        "L" ,
        "M" ,
        "N" ,
        "O" ,
        "P" ,
        "Q" ,
        "R" ,
        "S" ,
        "T" ,
        "U" ,
        "V" ,
        "W" ,
        "X" ,
        "Y" ,
        "Z" ,

        "1" ,
        "2" ,
        "3" ,
        "4" ,
        "5" ,
        "6" ,
        "7" ,
        "8" ,
        "9" ,
        "0" ,
        "RETURN" ,
        "ESCAPE" ,
        "BACKSPACE" ,
        "TAB" ,
        "SPACE" ,
        "MINUS" ,
        "EQUALS" ,
        "LEFTBRACKET" ,
        "RIGHTBRACKET" ,
        "BACKSLASH" , 
        "NONUSHASH" , 
        "SEMICOLON" ,
        "APOSTROPHE" ,
        "GRAVE" , 
        "COMMA" ,
        "PERIOD" ,
        "SLASH" ,
        "CAPSLOCK" ,
        "F1" ,
        "F2" ,
        "F3" ,
        "F4" ,
        "F5" ,
        "F6" ,
        "F7" ,
        "F8" ,
        "F9" ,
        "F10" ,
        "F11" ,
        "F12" ,
        "PRINTSCREEN" ,
        "SCROLLLOCK" ,
        "PAUSE" ,
        "INSERT" , 
        "HOME" ,
        "PAGEUP" ,
        "DELETE" ,
        "END" ,
        "PAGEDOWN" ,
        "RIGHT" ,
        "LEFT" ,
        "DOWN" ,
        "UP" ,
        "NUMLOCKCLEAR" , 
        "KP_DIVIDE" ,
        "KP_MULTIPLY" ,
        "KP_MINUS" ,
        "KP_PLUS" ,
        "KP_ENTER" ,
        "KP_1" ,
        "KP_2" ,
        "KP_3" ,
        "KP_4" ,
        "KP_5" ,
        "KP_6" ,
        "KP_7" ,
        "KP_8" ,
        "KP_9" ,
        "KP_0" ,
        "KP_PERIOD" ,
        "NONUSBACKSLASH" , 
        "APPLICATION" ,
        "POWER" , 
        "KP_EQUALS" ,
        "F13" ,
        "F14" ,
        "F15" ,
        "F16" ,
        "F17" ,
        "F18" ,
        "F19" ,
        "F20" ,
        "F21" ,
        "F22" ,
        "F23" ,
        "F24" ,
        "EXECUTE" ,
        "HELP" ,
        "MENU" ,
        "SELECT" ,
        "STOP" ,
        "AGAIN" ,
        "UNDO" ,
        "CUT" ,
        "COPY" ,
        "PASTE" ,
        "FIND" ,
        "MUTE" ,
        "VOLUMEUP" ,
        "VOLUMEDOWN" ,
        "KP_COMMA" ,
        "KP_EQUALSAS400" ,
        "INTERNATIONAL1" ,
        "INTERNATIONAL2" ,
        "INTERNATIONAL3" ,
        "INTERNATIONAL4" ,
        "INTERNATIONAL5" ,
        "INTERNATIONAL6" ,
        "INTERNATIONAL7" ,
        "INTERNATIONAL8" ,
        "INTERNATIONAL9" ,
        "LANG1" ,
        "LANG2" ,
        "LANG3" ,
        "LANG4" ,
        "LANG5" ,
        "LANG6" ,
        "LANG7" ,
        "LANG8" ,
        "LANG9" ,

        "ALTERASE" ,
        "SYSREQ" ,
        "CANCEL" ,
        "CLEAR" ,
        "PRIOR" ,
        "RETURN2" ,
        "SEPARATOR" ,
        "OUT" ,
        "OPER" ,
        "CLEARAGAIN" ,
        "CRSEL" ,
        "EXSEL" ,

        "KP_00" ,
        "KP_000" ,
        "THOUSANDSSEPARATOR" ,
        "DECIMALSEPARATOR" ,
        "CURRENCYUNIT" ,
        "CURRENCYSUBUNIT" ,
        "KP_LEFTPAREN" ,
        "KP_RIGHTPAREN" ,
        "KP_LEFTBRACE" ,
        "KP_RIGHTBRACE" ,
        "KP_TAB" ,
        "KP_BACKSPACE" ,
        "KP_A" ,
        "KP_B" ,
        "KP_C" ,
        "KP_D" ,
        "KP_E" ,
        "KP_F" ,
        "KP_XOR" ,
        "KP_POWER" ,
        "KP_PERCENT" ,
        "KP_LESS" ,
        "KP_GREATER" ,
        "KP_AMPERSAND" ,
        "KP_DBLAMPERSAND" ,
        "KP_VERTICALBAR" ,
        "KP_DBLVERTICALBAR" ,
        "KP_COLON" ,
        "KP_HASH" ,
        "KP_SPACE" ,
        "KP_AT" ,
        "KP_EXCLAM" ,
        "KP_MEMSTORE" ,
        "KP_MEMRECALL" ,
        "KP_MEMCLEAR" ,
        "KP_MEMADD" ,
        "KP_MEMSUBTRACT" ,
        "KP_MEMMULTIPLY" ,
        "KP_MEMDIVIDE" ,
        "KP_PLUSMINUS" ,
        "KP_CLEAR" ,
        "KP_CLEARENTRY" ,
        "KP_BINARY" ,
        "KP_OCTAL" ,
        "KP_DECIMAL" ,
        "KP_HEXADECIMAL" ,

        "LCTRL" ,
        "LSHIFT" ,
        "LALT" ,
        "LGUI" ,
        "RCTRL" ,
        "RSHIFT" ,
        "RALT" ,
        "RGUI" ,

        "MODE" ,
                                
                                
        "AUDIONEXT" ,
        "AUDIOPREV" ,
        "AUDIOSTOP" ,
        "AUDIOPLAY" ,
        "AUDIOMUTE" ,
        "MEDIASELECT" ,
        "WWW" ,
        "MAIL" ,
        "CALCULATOR" ,
        "COMPUTER" ,
        "AC_SEARCH" ,
        "AC_HOME" ,
        "AC_BACK" ,
        "AC_FORWARD" ,
        "AC_STOP" ,
        "AC_REFRESH" ,
        "AC_BOOKMARKS" ,


        "BRIGHTNESSDOWN" ,
        "BRIGHTNESSUP" ,
        "DISPLAYSWITCH" ,
                                        
        "KBDILLUMTOGGLE" ,
        "KBDILLUMDOWN" ,
        "KBDILLUMUP" ,
        "EJECT" ,
        "SLEEP" ,
        "APP1" ,
        "APP2" ,
        "AUDIOREWIND" ,
        "AUDIOFASTFORWARD" ,
        "DK_NUM_KEY"  
        "AUDIOMUTE" ,
        "MEDIASELECT" ,
        "WWW" ,
        "MAIL" ,
        "CALCULATOR" ,
        "COMPUTER" ,
        "AC_SEARCH" ,
        "AC_HOME" ,
        "AC_BACK" ,
        "AC_FORWARD" ,
        "AC_STOP" ,
        "AC_REFRESH" ,
        "AC_BOOKMARKS" ,
        "BRIGHTNESSDOWN" ,
        "BRIGHTNESSUP" ,
        "DISPLAYSWITCH" ,                           
        "KBDILLUMTOGGLE" ,
        "KBDILLUMDOWN" ,
        "KBDILLUMUP" ,
        "EJECT" ,
        "SLEEP" ,
        "APP1" ,
        "APP2" ,
        "AUDIOREWIND" ,
        "AUDIOFASTFORWARD" ,
        "NUM"  

    };

    
}
#endif // DK_KEY_CODE_HPP