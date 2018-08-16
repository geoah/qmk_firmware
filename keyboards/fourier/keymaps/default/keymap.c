#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FN1 1
#define _FN2 2
#define _FN3 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

#define LTC1 0x7100
#define LTC2 0x7101

bool layer_interrupted = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case LTC1: {
      if (record->event.pressed) {
        layer_interrupted = false;
        layer_on(1);
      } else {
        if (!layer_interrupted) {
          register_code(KC_SPACE);
          unregister_code(KC_SPACE);
        }
        layer_off(1);
      }
      return false;
      break;
    }
    case LTC2: {
      if (record->event.pressed) {
        layer_interrupted = false;
        layer_on(2);
      } else {
        if (!layer_interrupted) {
          register_code(KC_SPACE);
          unregister_code(KC_SPACE);
        }
        layer_off(2);
      }
      return false;
      break;
    }
    default: {
      layer_interrupted = true;
      break;
    }
  }
  return true;
}

#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_FN1 MO(_FN1)
#define KC_FN2 MO(_FN2)
#define KC_FN3 MO(_FN3)
#define KC_LTC1 LTC1 // LT(_FN1, KC_SPACE)
#define KC_LTC2 LTC2 // LT(_FN2, KC_SPACE)
#define KC_SPFN1 LT(_FN1, KC_SPACE)
#define KC_SPFN2 LT(_FN2, KC_SPACE)
#define KC_SPFN3 LT(_FN3, KC_SPACE)
#define KC_BSFN1 LT(_FN1, KC_BSPC)
#define KC_BSFN2 LT(_FN2, KC_BSPC)
#define KC_BSFN3 LT(_FN3, KC_BSPC)
#define KC_TBCT MT(MOD_LCTL, KC_TAB)
#define KC_RST RESET
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_kc(
 //,----+----+----+----+----+----|----+----+----+----+----+----+----.
    GESC, Q  , W  , E  , R  , T  , Y  , U  , I  , O  , P  ,    ,BSPC,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
    TBCT , A  , S  , D  , F  , G  , H  , J  , K  , L  ,QUOT, ENTER  ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
    LSFT   , Z  , X  , C  , V  , B  , N  , M  ,COMM,DOT ,SCOLON,RSFT,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
    MEH, LCTL ,LALT,LGUI , SPFN1  ,  BSFN2 , FN3 ,LBRC ,RBRC , SLSH
 //`-----+----+-----+----+--------|--------+-----+-----+-----+------'
  ),

  [_FN1] = LAYOUT_kc(
 //,----+----+----+----+----+----|----+----+----+----+----+----+----.
    TILD, 1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 0  ,MINS,EQL ,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
         ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,        ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
           ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,      ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
         ,    ,     ,    ,        ,        ,     ,MINS , EQL ,
 //`-----+----+-----+----+--------|--------+-----+-----+-----+------'
  ),

  [_FN2] = LAYOUT_kc(
 //,----+----+----+----+----+----|----+----+----+----+----+----+----.
    TILD,EXLM, AT ,HASH,DLR ,PERC,CIRC,AMPR,ASTR,LPRN,RPRN,UNDS,PLUS,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
         ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,        ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
           ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,      ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
         ,    ,     ,    ,        ,        ,     ,      ,     ,
 //`-----+----+-----+----+--------|--------+-----+-----+-----+------'
  ),

  [_FN3] = LAYOUT_kc(
 //,----+----+----+----+----+----|----+----+----+----+----+----+----.
    MRWD,MPLY,MFFD,VOLD,VOLU,    ,    ,    ,UP  ,    ,    ,    ,    ,
 //|----`----`----`----`----`----|----`----`----`----`----`----`----|
         ,    ,   ,    ,    ,     ,    ,LEFT,DOWN,RIGHT,   ,      ,
 //|-----`----`----`----`----`----|----`----`----`----`----`--------|
           ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,      ,
 //|-------`----`----`----`----`----|----`----`----`----`----`------|
         ,    ,     ,    ,        ,        ,     ,     ,     ,
 //`-----+----+-----+----+--------|--------+-----+-----+-----+------'
  )

};

void matrix_init_user(void) {
   // This will disable the red LEDs on the ProMicros
   DDRD &= ~(1<<5);
   PORTD &= ~(1<<5);
   DDRB &= ~(1<<0);
   PORTB &= ~(1<<0);
};