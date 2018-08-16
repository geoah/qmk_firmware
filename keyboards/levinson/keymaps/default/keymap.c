#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum custom_layers
{
	_QWERTY,
	_SHIFTED,
	_RAISED,
	_RAISED_SHIFTED
};

enum custom_keycodes {
  RAISE = SAFE_RANGE,
  SHIFT,
};

#define LONGPRESS_DELAY 150
#define LAYER_TOGGLE_DELAY 300

#define KC_TBCT MT(MOD_LCTL, KC_TAB)
#define KC_RSSPC LT(RAISE, KC_SPACE)
#define KC_RSBSP LT(RAISE, KC_BSPC)

#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_ortho_4x12( \
     KC_ESC,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_MINS, \
    KC_TBCT,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, \
     SHIFT ,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,   SHIFT, \
    _______, _______, _______, KC_LALT, KC_LGUI, KC_SPACE,KC_RSBSP,   RAISE,  KC_ENT, _______, _______, _______  \
  ),

  [_SHIFTED] = LAYOUT_ortho_4x12( \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  ),

  [_RAISED] = LAYOUT_ortho_4x12( \
    KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_EQL, \
    _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_LBRC, KC_RBRC, \
    _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  ),

  [_RAISED_SHIFTED] = LAYOUT_ortho_4x12( \
    KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LCBR, KC_RCBR, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PIPE, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  )

};

const uint16_t PROGMEM fn_actions[] = {
};

static uint16_t key_timer;

static bool singular_key = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

	uint8_t layer;
  layer = biton32(layer_state);  // get the current layer

  //custom layer handling for tri_layer,
  switch (keycode) {
  case RAISE:
  	if (record->event.pressed) {
      key_timer = timer_read();
      singular_key = true;
    	layer_on(_RAISED);
  	} else {
      if (timer_elapsed(key_timer) < LAYER_TOGGLE_DELAY || !singular_key) {
        layer_off(_RAISED);
      }
  	}
    update_tri_layer(_RAISED, _SHIFTED, _RAISED_SHIFTED);
  	return false;
  	break;

  //SHIFT is handled as LSHIFT in the general case
  case SHIFT:
  	if (record->event.pressed) {
      key_timer = timer_read();
      singular_key = true;
    	layer_on(_SHIFTED);
    	register_code(KC_LSFT);
  	} else {
    	if (timer_elapsed(key_timer) < LAYER_TOGGLE_DELAY || !singular_key) {
        layer_off(_SHIFTED);
    	  unregister_code(KC_LSFT);
      }
    }
    update_tri_layer(_RAISED, _SHIFTED, _RAISED_SHIFTED);
  	return false;
  	break;

  //If any other key was pressed during the layer mod hold period,
  //then the layer mod was used momentarily, and should block latching
  default:
    singular_key = false;
    break;
  }

  //FUNCSHIFT has been shifted by the SHIFT handling, some keys need to be excluded
  if (layer == _RAISED_SHIFTED) {
  	//F1-F12 should be sent as unshifted keycodes,
  	//and ] needs to be unshifted or it is sent as }
  	if ( (keycode >= KC_F1 && keycode <= KC_F12)
  	   || keycode == KC_RBRC ) {
  		if (record->event.pressed) {
              unregister_mods(MOD_LSFT);
          } else {
              register_mods(MOD_LSFT);
          }
  	}
  }

  return true;
};
