#ifndef _INCLUDED_INPUT_H
#define _INCLUDED_INPUT_H

// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *	Last updated by: Zach Bower
 *	Last updated on: Feb. 19, 2019
 *
 *	Purpose:
 *		This header class provides a reference to keyboard scancodes (which key was pressed) in a SDL
 *		Event. The contents of the class may be remapped to the end users needs, but come default
 *
 *
 *	Functions without comments are assumed to be a single line, set or get a single variable, and the
 *		comment is to be found next to the respective variable definition.
 */


namespace KeyInput{

    class Input
    {
    public:

        /*mouse codes*/
        enum
        {
            MLEFT_BUTTON = 1,
            MMIDDLE_BUTTON = 2,
            MRIGHT_BUTTON = 3,
            MWHEEL_UP = 4,
            MWHEEL_DOWN = 5
        };

        /*keyboard codes including international keys and some vendor specific keys
        eg volume up, pause audio*/
        enum
        {
            VK_UNKNOWN = 0,

            VK_A = 4,
            VK_B = 5,
            VK_C = 6,
            VK_D = 7,
            VK_E = 8,
            VK_F = 9,
            VK_G = 10,
            VK_H = 11,
            VK_I = 12,
            VK_J = 13,
            VK_K = 14,
            VK_L = 15,
            VK_M = 16,
            VK_N = 17,
            VK_O = 18,
            VK_P = 19,
            VK_Q = 20,
            VK_R = 21,
            VK_S = 22,
            VK_T = 23,
            VK_U = 24,
            VK_V = 25,
            VK_W = 26,
            VK_X = 27,
            VK_Y = 28,
            VK_Z = 29,

            VK_1 = 30,
            VK_2 = 31,
            VK_3 = 32,
            VK_4 = 33,
            VK_5 = 34,
            VK_6 = 35,
            VK_7 = 36,
            VK_8 = 37,
            VK_9 = 38,
            VK_0 = 39,

            VK_RETURN = 40,
            VK_ESCAPE = 41,
            VK_BACKSPACE = 42,
            VK_TAB = 43,
            VK_SPACE = 44,

            VK_MINUS = 45,
            VK_EQUALS = 46,
            VK_LEFTBRACKET = 47,
            VK_RIGHTBRACKET = 48,

            /*** UNCOMMON KEYS the descriptions taken from the SDL_SCANCODE documentation*/
                    VK_BACKSLASH = 49, /**< Located at the lower left of the return
									  *   VK on ISO VKboards and at the right end
									  *   of the QWERTY row on ANSI VKboards.
									  *   Produces REVERSE SOLIDUS (backslash) and
									  *   VERTICAL LINE in a US layout, REVERSE
									  *   SOLIDUS and VERTICAL LINE in a UK Mac
									  *   layout, NUMBER SIGN and TILDE in a UK
									  *   Windows layout, DOLLAR SIGN and POUND SIGN
									  *   in a Swiss German layout, NUMBER SIGN and
									  *   APOSTROPHE in a German layout, GRAVE
									  *   ACCENT and POUND SIGN in a French Mac
									  *   layout, and ASTERISK and MICRO SIGN in a
									  *   French Windows layout.
									  */
            VK_NONUSHASH = 50, /**< ISO USB VKboards actually use this code
									  *   instead of 49 for the same VK, but all
									  *   OSes I've seen treat the two codes
									  *   identically. So, as an implementor, unless
									  *   your VKboard generates both of those
									  *   codes and your OS treats them differently,
									  *   you should generate VK_BACKSLASH
									  *   instead of this code. As a user, you
									  *   should not rely on this code because SDL
									  *   will never generate it with most (all?)
									  *   VKboards.
									  */
            VK_SEMICOLON = 51,
            VK_APOSTROPHE = 52,
            VK_GRAVE = 53, /**< Located in the top left corner (on both ANSI
								  *   and ISO VKboards). Produces GRAVE ACCENT and
								  *   TILDE in a US Windows layout and in US and UK
								  *   Mac layouts on ANSI VKboards, GRAVE ACCENT
								  *   and NOT SIGN in a UK Windows layout, SECTION
								  *   SIGN and PLUS-MINUS SIGN in US and UK Mac
								  *   layouts on ISO VKboards, SECTION SIGN and
								  *   DEGREE SIGN in a Swiss German layout (Mac:
								  *   only on ISO VKboards), CIRCUMFLEX ACCENT and
								  *   DEGREE SIGN in a German layout (Mac: only on
								  *   ISO VKboards), SUPERSCRIPT TWO and TILDE in a
								  *   French Windows layout, COMMERCIAL AT and
								  *   NUMBER SIGN in a French Mac layout on ISO
								  *   VKboards, and LESS-THAN SIGN and GREATER-THAN
								  *   SIGN in a Swiss German, German, or French Mac
								  *   layout on ANSI VKboards.
								  */
            VK_COMMA = 54,
            VK_PERIOD = 55,
            VK_SLASH = 56,

            VK_CAPSLOCK = 57,

            VK_F1 = 58,
            VK_F2 = 59,
            VK_F3 = 60,
            VK_F4 = 61,
            VK_F5 = 62,
            VK_F6 = 63,
            VK_F7 = 64,
            VK_F8 = 65,
            VK_F9 = 66,
            VK_F10 = 67,
            VK_F11 = 68,
            VK_F12 = 69,

            VK_PRINTSCREEN = 70,
            VK_SCROLLLOCK = 71,
            VK_PAUSE = 72,
            VK_INSERT = 73, /**< insert on PC, help on some Mac VKboards (but
									   does send code 73, not 117) */
            VK_HOME = 74,
            VK_PAGEUP = 75,
            VK_DELETE = 76,
            VK_END = 77,
            VK_PAGEDOWN = 78,
            VK_RIGHT = 79,
            VK_LEFT = 80,
            VK_DOWN = 81,
            VK_UP = 82,

            VK_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac VKboards*/
            VK_KP_DIVIDE = 84,
            VK_KP_MULTIPLY = 85,
            VK_KP_MINUS = 86,
            VK_KP_PLUS = 87,
            VK_KP_ENTER = 88,
            VK_KP_1 = 89,
            VK_KP_2 = 90,
            VK_KP_3 = 91,
            VK_KP_4 = 92,
            VK_KP_5 = 93,
            VK_KP_6 = 94,
            VK_KP_7 = 95,
            VK_KP_8 = 96,
            VK_KP_9 = 97,
            VK_KP_0 = 98,
            VK_KP_PERIOD = 99,

            VK_NONUSBACKSLASH = 100, /**< This is the additional VK that ISO
											*   VKboards have over ANSI ones,
											*   located between left shift and Y.
											*   Produces GRAVE ACCENT and TILDE in a
											*   US or UK Mac layout, REVERSE SOLIDUS
											*   (backslash) and VERTICAL LINE in a
											*   US or UK Windows layout, and
											*   LESS-THAN SIGN and GREATER-THAN SIGN
											*   in a Swiss German, German, or French
											*   layout. */
            VK_APPLICATION = 101, /**< windows contextual menu, compose */
            VK_POWER = 102, /**Some Mac VKboards have a power VK. */
            VK_KP_EQUALS = 103,
            VK_F13 = 104,
            VK_F14 = 105,
            VK_F15 = 106,
            VK_F16 = 107,
            VK_F17 = 108,
            VK_F18 = 109,
            VK_F19 = 110,
            VK_F20 = 111,
            VK_F21 = 112,
            VK_F22 = 113,
            VK_F23 = 114,
            VK_F24 = 115,
            VK_EXECUTE = 116,
            VK_HELP = 117,
            VK_MENU = 118,
            VK_SELECT = 119,
            VK_STOP = 120,
            VK_AGAIN = 121,   /**< redo */
            VK_UNDO = 122,
            VK_CUT = 123,
            VK_COPY = 124,
            VK_PASTE = 125,
            VK_FIND = 126,
            VK_MUTE = 127,
            VK_VOLUMEUP = 128,
            VK_VOLUMEDOWN = 129,
            VK_LOCKINGCAPSLOCK = 130,
            VK_LOCKINGNUMLOCK = 131,
            VK_LOCKINGSCROLLLOCK = 132,
            VK_KP_COMMA = 133,
            VK_KP_EQUALSAS400 = 134,

            VK_INTERNATIONAL1 = 135, /**< used on Asian VKboards, more information in USB documentation*/
            VK_INTERNATIONAL2 = 136,
            VK_INTERNATIONAL3 = 137, /**< Yen */
            VK_INTERNATIONAL4 = 138,
            VK_INTERNATIONAL5 = 139,
            VK_INTERNATIONAL6 = 140,
            VK_INTERNATIONAL7 = 141,
            VK_INTERNATIONAL8 = 142,
            VK_INTERNATIONAL9 = 143,
            VK_LANG1 = 144, /**< Hangul/English toggle */
            VK_LANG2 = 145, /**< Hanja conversion */
            VK_LANG3 = 146, /**< Katakana */
            VK_LANG4 = 147, /**< Hiragana */
            VK_LANG5 = 148, /**< Zenkaku/Hankaku */
            VK_LANG6 = 149, /**< reserved */
            VK_LANG7 = 150, /**< reserved */
            VK_LANG8 = 151, /**< reserved */
            VK_LANG9 = 152, /**< reserved */

            VK_ALTERASE = 153, /**< Erase-Eaze */
            VK_SYSREQ = 154,
            VK_CANCEL = 155,
            VK_CLEAR = 156,
            VK_PRIOR = 157,
            VK_RETURN2 = 158,
            VK_SEPARATOR = 159,
            VK_OUT = 160,
            VK_OPER = 161,
            VK_CLEARAGAIN = 162,
            VK_CRSEL = 163,
            VK_EXSEL = 164,

            VK_KP_00 = 176,
            VK_KP_000 = 177,
            VK_THOUSANDSSEPARATOR = 178,
            VK_DECIMALSEPARATOR = 179,
            VK_CURRENCYUNIT = 180,
            VK_CURRENCYSUBUNIT = 181,
            VK_KP_LEFTPAREN = 182,
            VK_KP_RIGHTPAREN = 183,
            VK_KP_LEFTBRACE = 184,
            VK_KP_RIGHTBRACE = 185,
            VK_KP_TAB = 186,
            VK_KP_BACKSPACE = 187,
            VK_KP_A = 188,
            VK_KP_B = 189,
            VK_KP_C = 190,
            VK_KP_D = 191,
            VK_KP_E = 192,
            VK_KP_F = 193,
            VK_KP_XOR = 194,
            VK_KP_POWER = 195,
            VK_KP_PERCENT = 196,
            VK_KP_LESS = 197,
            VK_KP_GREATER = 198,
            VK_KP_AMPERSAND = 199,
            VK_KP_DBLAMPERSAND = 200,
            VK_KP_VERTICALBAR = 201,
            VK_KP_DBLVERTICALBAR = 202,
            VK_KP_COLON = 203,
            VK_KP_HASH = 204,
            VK_KP_SPACE = 205,
            VK_KP_AT = 206,
            VK_KP_EXCLAM = 207,
            VK_KP_MEMSTORE = 208,
            VK_KP_MEMRECALL = 209,
            VK_KP_MEMCLEAR = 210,
            VK_KP_MEMADD = 211,
            VK_KP_MEMSUBTRACT = 212,
            VK_KP_MEMMULTIPLY = 213,
            VK_KP_MEMDIVIDE = 214,
            VK_KP_PLUSMINUS = 215,
            VK_KP_CLEAR = 216,
            VK_KP_CLEARENTRY = 217,
            VK_KP_BINARY = 218,
            VK_KP_OCTAL = 219,
            VK_KP_DECIMAL = 220,
            VK_KP_HEXADECIMAL = 221,

            VK_LCTRL = 224,
            VK_LSHIFT = 225,
            VK_LALT = 226, /**< alt, option */
            VK_LGUI = 227, /**< windows, command (apple), meta */
            VK_RCTRL = 228,
            VK_RSHIFT = 229,
            VK_RALT = 230, /**< alt gr, option */
            VK_RGUI = 231, /**< windows, command (apple), meta */

            VK_MODE = 257,    /**< I'm not sure if this is really not covered
									 *   by any of the above, but since there's a
									 *   special KMOD_MODE for it I'm adding it here
									 */

            /*@}*//*Usage page 0x07*/

            /**
             *  \name Usage page 0x0C
             *
             *  These values are mapped from usage page 0x0C (USB consumer page).
             */
            /*@{*/

                    VK_AUDIONEXT = 258,
            VK_AUDIOPREV = 259,
            VK_AUDIOSTOP = 260,
            VK_AUDIOPLAY = 261,
            VK_AUDIOMUTE = 262,
            VK_MEDIASELECT = 263,
            VK_WWW = 264,
            VK_MAIL = 265,
            VK_CALCULATOR = 266,
            VK_COMPUTER = 267,
            VK_AC_SEARCH = 268,
            VK_AC_HOME = 269,
            VK_AC_BACK = 270,
            VK_AC_FORWARD = 271,
            VK_AC_STOP = 272,
            VK_AC_REFRESH = 273,
            VK_AC_BOOKMARKS = 274,

            /*@}*//*Usage page 0x0C*/

            /**
             *  \name Walther VKs
             *
             *  These are values that Christian Walther added (for mac VKboard?).
             */
            /*@{*/

                    VK_BRIGHTNESSDOWN = 275,
            VK_BRIGHTNESSUP = 276,
            VK_DISPLAYSWITCH = 277, /**< display mirroring/dual display
											   switch, video mode switch */
            VK_KBDILLUMTOGGLE = 278,
            VK_KBDILLUMDOWN = 279,
            VK_KBDILLUMUP = 280,
            VK_EJECT = 281,
            VK_SLEEP = 282,

            VK_APP1 = 283,
            VK_APP2 = 284,
        };
    };

#endif
