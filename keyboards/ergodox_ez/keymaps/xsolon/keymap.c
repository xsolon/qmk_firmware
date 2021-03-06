#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define VSFN 3 // Visual Studio + FNs

#define MACRO_PUBLIC 10
#define MACRO_PRIVATE 11

#define MACRO_STATIC 12
#define MACRO_CONST 13

#define MACRO_VOID 14
#define MACRO_VAR 15
#define MACRO_STRING 16

#define MACRO_INT 17
#define MACRO_FLOAT 18
#define MACRO_BOOL 19

#define MACRO_RETURN 20
#define MACRO_NULL 21
#define MACRO_BREAK 22

#define MACRO_TODO 23
#define MACRO_NEW 24
#define MACRO_USING 25
#define MACRO_GETSET 26
#define MACRO_FORMAT 27
#define MACRO_PROMISE 28

enum custom_keycodes {
	PLACEHOLDER = SAFE_RANGE, // can always be here
	EPRM,
	VRSN,
	RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Keymap 0: Basic layer
	*
	* ,--------------------------------------------------.           ,--------------------------------------------------.
	* | Esc    |   1  |   2  |   3  |   4  |   5  | Cut  |           |  -   |   6  |   7  |   8  |   9  |   0  | BackS  |
	* |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
	* | Tab    |   Q  |   W  |   E  |   R  |   T  | Paste|           | Undo |   Y  |   U  |   I  |   O  |   P  |   \    |
	* |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
	* | Tab/L2 |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L3|' / Cmd |
	* |--------+------+------+------+------+------| Copy |           | Redo |------+------+------+------+------+--------|
	* | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
	* `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
	*   |Ctrl  | Win  |Alt	  | L1   | Alt  |                         		|  Alt | Left |Down  | Up   | Right  |
	*   `----------------------------------'                                `----------------------------------'
	*                                        ,-------------.       ,---------------.
	*                                        | Esc  | Del  |       | App  |Ctrl/Esc|
	*                                 ,------|------|------|       |------+--------+------.
	*                                 |      |      | Home |       | PgUp |        |      |
	*                                 | Space|BackS/|------|       |------|  Tab   |Enter/|
	*                                 | /L1  |L2    |End/L3|       | PgDn |        |L1    |
	*                                 `--------------------'       `----------------------'
	*/
	// If it accepts an argument (i.e, is a function), it doesn't need KC_.
	// Otherwise, it needs KC_*
	[BASE] = LAYOUT_ergodox(  // layer 0 : default
					  // left hand
		KC_ESC,         KC_1,         KC_2,   		KC_3,   KC_4,   KC_5,   LCTL(KC_X),
		KC_TAB,         KC_Q,         KC_W,   		KC_E,   KC_R,   KC_T,   LCTL(KC_V),
		LT(MDIA,KC_TAB),KC_A,	      KC_S,	   		KC_D,   KC_F,   KC_G,
		KC_LSFT,        KC_Z,	      KC_X,   		KC_C,   KC_V,   KC_B,   LCTL(KC_C),
		KC_LCTL,	KC_LGUI,      KC_LALT,MO(SYMB),KC_LALT,
		KC_ESC,  KC_DELT,
		KC_HOME,
		LT(SYMB,KC_SPC),LT(MDIA,KC_BSPC),LT(VSFN,KC_END),

		// right hand
		KC_MINS,		KC_6,		KC_7,		KC_8,   KC_9,			KC_0,				KC_BSPC,
		LCTL(KC_Z),    	KC_Y,		KC_U,		KC_I,   KC_O,			KC_P,				KC_BSLS,
						KC_H,		KC_J,		KC_K,   KC_L,			LT(VSFN, KC_SCLN),	GUI_T(KC_QUOT),
		LCTL(KC_Y),		KC_N, KC_M, KC_COMM,	KC_DOT, CTL_T(KC_SLSH), KC_RSFT,
		KC_LALT, KC_LEFT,KC_DOWN,KC_UP, KC_RGHT,
		ALT_T(KC_APP),        CTL_T(KC_ESC),
		KC_PGUP,
		KC_PGDN,KC_TAB, LT(SYMB,KC_ENT)
	),
	/* Keymap 1: Symbol Layer
	*
	* ,---------------------------------------------------.           ,--------------------------------------------------.
	* |Version |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
	* |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
	* | Shf+F5 |   {  |   }  |  [   |   ]  |  |    |	  |           |      | P Up | Home | End  |  =   |   *  |   F12  |
	* |--------+------+------+------+------+-------|      |           |      |------+------+------+------+------+--------|
	* | Shf+F6 | End  | Back | Del  |Enter | Esc   |------|           |------| Left | Down |  Up  |Right |   +  |        |
	* |--------+------+------+------+------+------ | Ctrl+|           |      |------+------+------+------+------+------- |
	* |		   |   %  |   ^  |Close |   _  |   ~   |   \  |           |      | PDown| App  |   -  |   3  |   \  |        |
	* `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
	*   |      |  F5  | F10  |  F11 |       |                                       |      |    . |   0  |   =  |      |
	*   `-----------------------------------'                                       `----------------------------------'
	*                                        ,-------------.       ,-------------.
	*                                        |Animat| Bri- |       |Toggle|Solid |
	*                                 ,------|------|------|       |------+------+------.
	*                                 |		 |      | Bri+ |       |      |Hue-  |Hue+  |
	*                                 |      | EPRM |------|       |------|      |      |
	*                                 |      |      |      |       |      |      |      |
	*                                 `--------------------'       `--------------------'
	*/
	// SYMBOLS
	[SYMB] = LAYOUT_ergodox(
		// left hand
		VRSN,				KC_F1,		KC_F2,		KC_F3,			KC_F4,			KC_F5,		KC_TRNS,
		LSFT(KC_F5),		KC_LCBR,	KC_RCBR,	KC_LBRC,		KC_RBRC,		KC_PIPE,	KC_TRNS,
		LSFT(KC_F6),		KC_HOME,	KC_BSPC,	KC_DELT,		KC_ENT,			KC_ESC,
		KC_TRNS,			KC_PERC,	KC_CIRC,	LCTL(KC_F4),	LSFT(KC_MINS),	KC_TILD,	LCTL(KC_BSLS),
		KC_TRNS,			KC_F5,		KC_F10,		KC_F11, KC_TRNS,
											RGB_MOD, RGB_VAD,
													 RGB_VAI,
									  KC_TRNS, EPRM, KC_TRNS,
		// right hand
		KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
		KC_TRNS, KC_PGUP, KC_HOME, KC_END, KC_EQL, KC_ASTR, KC_F12,
				 KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_PLUS, KC_TRNS,
		KC_TRNS, KC_PGDN, ALT_T(KC_APP), KC_MINS, KC_3, KC_BSLS, KC_TRNS,
		KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
		RGB_TOG, RGB_SLD,
		KC_TRNS,
		KC_TRNS, RGB_HUD, RGB_HUI
	),
	/* Keymap 2: Media and mouse keys
	*
	* ,--------------------------------------------------.           ,--------------------------------------------------.
	* |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
	* |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
	* |        |      |      | MsUp |      |      |      |           |      |MwUp  |      |      |      |      |        |
	* |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
	* |        |      |MsLeft|MsDown|MsRght| Rclk |------|           |------|MsLeft|MsDown| MsUp |MsRght|      |  Play  |
	* |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
	* |        |      |      |      |      |      |      |           |      |MwDn  |      | Prev | Next |      |  MwUp  |
	* `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
	*   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      | MwDn  |
	*   `----------------------------------'                                       `----------------------------------'
	*                                        ,-------------.       ,-------------.
	*                                        |      |      |       | Mclk |      |
	*                                 ,------|------|------|       |------+------+------.
	*                                 |      |      |      |       | Mbn4 |Brwser|Brwser|
	*                                 |Lclk  |      |------|       |------|Fwd   |Back  |
	*                                 |      |      |      |       | Mbn5 |      |      |
	*                                 `--------------------'       `--------------------'
	*/
	// MEDIA AND MOUSE
	[MDIA] = LAYOUT_ergodox(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN2,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
		KC_TRNS, KC_TRNS,
		KC_TRNS,
		KC_BTN1, KC_TRNS, KC_TRNS,
		// right hand
		KC_TRNS,	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS,	KC_WH_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
					KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_TRNS, KC_MPLY,
		KC_TRNS,	KC_WH_D, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_WH_U,
		KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_WH_D,
		KC_MS_BTN3, KC_TRNS,
		KC_MS_BTN4,
		KC_MS_BTN5, KC_WFWD, KC_WBAK
	),
	/* Keymap 3:  Visual Studio Layer
	*
	* ,--------------------------------------------------.           ,--------------------------------------------------.
	* |        |  F1  |  F2  |  F3  |Alt+F4|  F5  |      |           | Calc |ShftF6     |  F7  |Shift+F6| F12  |  F10 |   F11  |
	* |--------+------+------+------+------+-------------|           |------+-----------+------+--------+------+------+--------|
	* |        |Public|Static|string|int   |return|      |           |      |RTs PrevTab|      |        |      |      |   F12  |
	* |--------+------+------+------+------+------|      |           |      |-----------+------+--------+------+------+--------|
	* |        |Privat|Const |var   |float |null  |------|           |------|new        |      |        |      |      |        |
	* |--------+------+------+------+------+------|      |           |      |-----------+------+--------+------+------+--------|
	* |        |TODO  |using |void  |bool  |break;|      |           |      |RTs NextTab|      |        |      |      |        |
	* `--------+------+------+------+------+-------------'           `-------------+------+--------+------+------+--------'
	*   |      | Alt  |getset|proms |      |                                       |      |        |      |      |      |
	*   `----------------------------------'                                       `----------------------------------'
	*                                        ,-------------.       ,-------------.
	*                                        | F5   | F10  |       |      |      |
	*                                 ,------|------|------|       |------+------+------.
	*                                 |      |      | F11  |       |      |      |      |
	*                                 |Format|Reshar|------|       |------|      |      |
	*                                 |Doc   |Clean | F12  |       |      |      |      |
	*                                 `--------------------'       `--------------------'
	*/
	// VS + FKEYS + MACROS
	[VSFN] = LAYOUT_ergodox(
		// left hand
		KC_TRNS, KC_F1,				KC_F2, KC_F3, LALT(KC_F4), KC_F5, KC_TRNS,
		KC_TRNS, M(MACRO_PUBLIC),	M(MACRO_STATIC),	M(MACRO_STRING),	M(MACRO_INT),	M(MACRO_RETURN),	KC_TRNS,
		KC_TRNS, M(MACRO_PRIVATE),	M(MACRO_CONST),		M(MACRO_VAR),		M(MACRO_FLOAT), M(MACRO_NULL),
		KC_TRNS, M(MACRO_TODO),		M(MACRO_USING),		M(MACRO_VOID),		M(MACRO_BOOL),  M(MACRO_BREAK),		KC_TRNS,
		KC_TRNS, KC_LALT,			M(MACRO_GETSET),	M(MACRO_PROMISE),	KC_TRNS,
										 KC_F5,			KC_F10,
														KC_F11,
						M(MACRO_FORMAT), LCTL(KC_4),	KC_F12,
		// right hand
		KC_CALCULATOR,	LSFT(KC_F6), KC_F7, LSFT(KC_F6), KC_F12, KC_F10, KC_F11,
		KC_TRNS,		ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT, KC_PGUP), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,
		M(MACRO_NEW),	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS,		ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT, KC_PGDN), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS,		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS,		KC_TRNS,
		KC_TRNS,
		KC_TRNS,		KC_TRNS, KC_TRNS
	)

};

const uint16_t PROGMEM fn_actions[] = {
	[1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	// MACRODOWN only works in this function
	switch (id) {
	case 0:
		if (record->event.pressed) {
			SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
		}
		break;
	case 1:
		if (record->event.pressed) { // For resetting EEPROM
			eeconfig_init();
		}
		break;
	case MACRO_PUBLIC:
		if (record->event.pressed) {
			SEND_STRING("public ");
		}
		break;
	case MACRO_PRIVATE:
		if (record->event.pressed) {
			SEND_STRING("private");
		}
		break;
	case MACRO_STATIC:
		if (record->event.pressed) {
			SEND_STRING("static ");
		}
		break;
	case MACRO_CONST:
		if (record->event.pressed) {
			SEND_STRING("const ");
		}
		break;
	case MACRO_VOID:
		if (record->event.pressed) {
			SEND_STRING("void method() {}");
		}
		break;
	case MACRO_VAR:
		if (record->event.pressed) {
			SEND_STRING("var p = new VAR();");
		}
		break;
	case MACRO_STRING:
		if (record->event.pressed) {
			SEND_STRING("string s = ;");
		}
		break;
	case MACRO_BOOL:
		if (record->event.pressed) {
			SEND_STRING("bool b = false;");
		}
		break;
	case MACRO_INT:
		if (record->event.pressed) {
			SEND_STRING("int i = 0;");
		}
		break;
	case MACRO_FLOAT:
		if (record->event.pressed) {
			SEND_STRING("float ");
		}
		break;
	case MACRO_RETURN:
		if (record->event.pressed) {
			SEND_STRING("return ;");
		}
		break;
	case MACRO_NULL:
		if (record->event.pressed) {
			SEND_STRING("null ");
		}
	case MACRO_BREAK:
		if (record->event.pressed) {
			SEND_STRING("break;");
		}
		break;
	case MACRO_TODO:
		if (record->event.pressed) {
			SEND_STRING("///TODO ");
		}
		break;
	case MACRO_NEW:
		if (record->event.pressed) {
			SEND_STRING("new ();");
		}
		break;
	case MACRO_USING:
		if (record->event.pressed) {
			SEND_STRING("using(var d = new ()){}");
		}
		break;
	case MACRO_GETSET:
		if (record->event.pressed) {
			SEND_STRING("{get;set;}");
		}
		break;
	case MACRO_FORMAT:
		if (record->event.pressed) {
			return MACRO(D(LCTL), T(E), T(D), U(LCTL), END);
		}
		break;

	case MACRO_PROMISE:
		if (record->event.pressed) {
			SEND_STRING("return $.Deferred(function(dfd) { dfd.resolve(); }).promise();");
		}
		break;

	}
	return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		// dynamically generate these.
	case EPRM:
		if (record->event.pressed) {
			eeconfig_init();
		}
		return false;
		break;
	case VRSN:
		if (record->event.pressed) {
			SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
		}
		return false;
		break;
	case RGB_SLD:
		if (record->event.pressed) {
#ifdef RGBLIGHT_ENABLE
			rgblight_mode(1);
#endif
		}
		return false;
		break;
	}
	return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

	uint8_t layer = biton32(layer_state);

	ergodox_board_led_off();
	ergodox_right_led_1_off();
	ergodox_right_led_2_off();
	ergodox_right_led_3_off();
	switch (layer) {
		// TODO: Make this relevant to the ErgoDox EZ.
	case SYMB:
		ergodox_right_led_1_on();
		break;
	case MDIA:
		ergodox_right_led_2_on();
		break;
	case 3:
		ergodox_right_led_3_on();
		break;
	default:
		// none
		break;
	}

};
