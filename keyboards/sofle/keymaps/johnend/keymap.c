 /* Copyright 2021 Dane Evans
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
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
  // SOFLE RGB
#include <stdio.h>

#include QMK_KEYBOARD_H

#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations
#define SET_INDICATORS(hsv) \
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, hsv}
#define SET_UNDERGLOW(hsv) \
	{1, 6, hsv}, \
    {35+1, 6,hsv}
#define SET_NUMPAD(hsv)     \
	{35+15, 5, hsv},\
	  {35+22, 3, hsv},\
	  {35+27, 3, hsv}
#define SET_NUMROW(hsv) \
	{10, 2, hsv}, \
		{20, 2, hsv}, \
		{30, 2, hsv}, \
	  {35+ 10, 2, hsv}, \
	  {35+ 20, 2, hsv}, \
	  {35+ 30, 2, hsv}
#define SET_INNER_COL(hsv)	\
	{33, 4, hsv}, \
	  {35+ 33, 4, hsv}

#define SET_OUTER_COL(hsv) \
	{7, 4, hsv}, \
	  {35+ 7, 4, hsv}
#define SET_THUMB_CLUSTER(hsv) 	\
	{25, 2, hsv}, \
	  {35+ 25, 2, hsv}
#define SET_LAYER_ID(hsv) 	\
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
		{1, 6, hsv}, \
    {35+1, 6, hsv}, \
		{7, 4, hsv}, \
	  {35+ 7, 4, hsv}, \
		{25, 2, hsv}, \
	  {35+ 25, 2, hsv}

#define KC_CAPP         // Capture portion of screen
#define KC_CPYP   // Copy portion of screen

enum sofle_layers {
    _DEFAULTS = 0,
    _QWERTY = 0,
    _LINUX,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMPAD,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_LINUX,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌────────────────┬───┬───┬───┬───┬────────┐                       ┌───────────────┬───┬───┬─────┬───┬───┐
//    │      esc       │ 1 │ 2 │ 3 │ 4 │   5    │                       │       6       │ 7 │ 8 │  9  │ 0 │ 󰁮 │
//    ├────────────────┼───┼───┼───┼───┼────────┤                       ├───────────────┼───┼───┼─────┼───┼───┤
//    │       `        │ q │ w │ e │ r │   t    │                       │       y       │ u │ i │  o  │ p │ - │
//    ├────────────────┼───┼───┼───┼───┼────────┤                       ├───────────────┼───┼───┼─────┼───┼───┤
//    │ LT(_NUMPAD, 󰌒) │ a │ s │ d │ f │   g    │                       │       h       │ j │ k │  l  │ ; │ ' │
//    ├────────────────┼───┼───┼───┼───┼────────┼──────────┐   ┌────────┼───────────────┼───┼───┼─────┼───┼───┤
//    │       󰘶        │ z │ x │ c │ v │   b    │         │   │ TO(1)  │       n       │ m │ , │  .  │ / │ 󰘶 │
//    └────────────────┴───┼───┼───┼───┼────────┼──────────┤   ├────────┼───────────────┼───┼───┼─────┼───┴───┘
//                         │ 󰘴 │ 󰘵 │ 󱞡 │ (esc) │ 󰘳/(ent) │   │ 󰘴(spc) │ LT(_RAISE, 󰁮) │  │ 󰘵 │ 󰘳/ │
//                         └───┴───┴───┴────────┴──────────┘   └────────┴───────────────┴───┴───┴─────┘
[_QWERTY] = LAYOUT(
  KC_ESC              , KC_1 , KC_2    , KC_3    , KC_4     , KC_5          ,                                       KC_6                , KC_7    , KC_8    , KC_9    , KC_0    , KC_BSPC,
  KC_GRV              , KC_Q , KC_W    , KC_E    , KC_R     , KC_T          ,                                       KC_Y                , KC_U    , KC_I    , KC_O    , KC_P    , KC_MINS,
  LT(_NUMPAD, KC_TAB) , KC_A , KC_S    , KC_D    , KC_F     , KC_G          ,                                       KC_H                , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT,
  KC_LSFT             , KC_Z , KC_X    , KC_C    , KC_V     , KC_B          , KC_MPLY        ,     TO(1)          , KC_N                , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT,
                               KC_LCTL , KC_LALT , KC_LOWER , MEH_T(KC_ESC) , LGUI_T(KC_ENT) ,     LCTL_T(KC_SPC) , LT(_RAISE, KC_BSPC) , KC_HYPR , KC_RALT , KC_LGUI
),

//    ┌────────────────┬───┬───┬───┬───┬────────┐                       ┌───────────────┬───┬───┬─────┬───┬───┐
//    │      esc       │ 1 │ 2 │ 3 │ 4 │   5    │                       │       6       │ 7 │ 8 │  9  │ 0 │ 󰁮 │
//    ├────────────────┼───┼───┼───┼───┼────────┤                       ├───────────────┼───┼───┼─────┼───┼───┤
//    │       `        │ q │ w │ e │ r │   t    │                       │       y       │ u │ i │  o  │ p │ - │
//    ├────────────────┼───┼───┼───┼───┼────────┤                       ├───────────────┼───┼───┼─────┼───┼───┤
//    │ LT(_NUMPAD, 󰌒) │ a │ s │ d │ f │   g    │                       │       h       │ j │ k │  l  │ ; │ ' │
//    ├────────────────┼───┼───┼───┼───┼────────┼──────────┐   ┌────────┼───────────────┼───┼───┼─────┼───┼───┤
//    │       󰘶        │ z │ x │ c │ v │   b    │         │   │ TO(0)  │       n       │ m │ , │  .  │ / │ 󰘶 │
//    └────────────────┴───┼───┼───┼───┼────────┼──────────┤   ├────────┼───────────────┼───┼───┼─────┼───┴───┘
//                         │ 󰘴 │ 󰘵 │ 󱞡 │ (esc) │ 󰘳/(ent) │   │ 󰘴(spc) │ LT(_RAISE, 󰁮) │  │ 󰘵 │ 󰘳/ │
//                         └───┴───┴───┴────────┴──────────┘   └────────┴───────────────┴───┴───┴─────┘
[_LINUX] = LAYOUT(
  KC_ESC              , KC_1 , KC_2    , KC_3    , KC_4     , KC_5          ,                                       KC_6                , KC_7    , KC_8    , KC_9    , KC_0    , KC_BSPC,
  KC_GRV              , KC_Q , KC_W    , KC_E    , KC_R     , KC_T          ,                                       KC_Y                , KC_U    , KC_I    , KC_O    , KC_P    , KC_MINS,
  LT(_NUMPAD, KC_TAB) , KC_A , KC_S    , KC_D    , KC_F     , KC_G          ,                                       KC_H                , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT,
  KC_LSFT             , KC_Z , KC_X    , KC_C    , KC_V     , KC_B          , KC_MPLY        ,     TO(0)          , KC_N                , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT,
                               KC_LCTL , KC_LALT , KC_LOWER , MEH_T(KC_ESC) , LGUI_T(KC_ENT) ,     LCTL_T(KC_SPC) , LT(_RAISE, KC_BSPC) , KC_HYPR , KC_RALT , KC_LGUI
),

//    ┌──────┬──────┬──────┬──────┬──────┬──────┐               ┌──────┬──────┬──────┬──────┬────┬─────┐
//    │      │  f1  │  f2  │  f3  │  f4  │  f5  │               │ f12  │  no  │  no  │  no  │ no │  󰹾  │
//    ├──────┼──────┼──────┼──────┼──────┼──────┤               ├──────┼──────┼──────┼──────┼────┼─────┤
//    │  no  │  no  │  no  │  =   │ 󰘶(,) │ 󰘶(.) │               │  ;   │ 󰘶(9) │ 󰘶(0) │  no  │ no │ no  │
//    ├──────┼──────┼──────┼──────┼──────┼──────┤               ├──────┼──────┼──────┼──────┼────┼─────┤
//    │ 󰘶(󰌒) │ 󰘶(=) │  -   │  no  │ 󰘶([) │ 󰘶(]) │               │ 󰘶(;) │  [   │  ]   │ 󰘶(\) │ no │ no  │
//    ├──────┼──────┼──────┼──────┼──────┼──────┼─────┐   ┌─────┼──────┼──────┼──────┼──────┼────┼─────┤
//    │      │ 󰘶(1) │ 󰘶(2) │ 󰘶(3) │ 󰘶(4) │ 󰘶(5) │     │   │     │ 󰘶(6) │ 󰘶(7) │ 󰘶(8) │  no  │ \  │     │
//    └──────┴──────┼──────┼──────┼──────┼──────┼─────┤   ├─────┼──────┼──────┼──────┼──────┼────┴─────┘
//                  │      │      │      │      │     │   │     │      │      │      │      │
//                  └──────┴──────┴──────┴──────┴─────┘   └─────┴──────┴──────┴──────┴──────┘
[_LOWER] = LAYOUT(
  _______      , KC_F1          , KC_F2      , KC_F3      , KC_F4          , KC_F5         ,                         KC_F12        , XXXXXXX    , XXXXXXX    , XXXXXXX       , XXXXXXX , KC_DEL ,
  XXXXXXX      , XXXXXXX        , XXXXXXX    , KC_EQUAL   , LSFT(KC_COMMA) , LSFT(KC_DOT)  ,                         KC_SCLN       , LSFT(KC_9) , LSFT(KC_0) , KC_NO         , KC_NO   , KC_NO  ,
  LSFT(KC_TAB) , LSFT(KC_EQUAL) , KC_MINUS   , KC_NO      , LSFT(KC_LBRC)  , LSFT(KC_RBRC) ,                         LSFT(KC_SCLN) , KC_LBRC    , KC_RBRC    , LSFT(KC_BSLS) , XXXXXXX , XXXXXXX,
  _______      , LSFT(KC_1)     , LSFT(KC_2) , LSFT(KC_3) , LSFT(KC_4)     , LSFT(KC_5)    , _______ ,     _______ , LSFT(KC_6)    , LSFT(KC_7) , LSFT(KC_8) , KC_NO         , KC_BSLS , _______,
                                  _______    , _______    , _______        , _______       , _______ ,     _______ , _______       , _______    , _______    , _______
),

//    ┌─────┬────┬─────┬─────┬──────────────┬───────────┐               ┌──────┬──────┬──────┬──────┬────┬─────┐
//    │ no  │   │    │  󰒮  │             │     󰒭     │               │  no  │  no  │  no  │  no  │ no │  󰹾  │
//    ├─────┼────┼─────┼─────┼──────────────┼───────────┤               ├──────┼──────┼──────┼──────┼────┼─────┤
//    │ no  │ no │ no  │ no  │ 󰘳/(󰘶(󰘴(4))) │ 󰘳/(󰘶(4)) │               │ home │ pgdn │ pgup │ end  │ no │ no  │
//    ├─────┼────┼─────┼─────┼──────────────┼───────────┤               ├──────┼──────┼──────┼──────┼────┼─────┤
//    │ no  │ no │ no  │ no  │     esc      │    no     │               │     │     │     │     │ no │ no  │
//    ├─────┼────┼─────┼─────┼──────────────┼───────────┼─────┐   ┌─────┼──────┼──────┼──────┼──────┼────┼─────┤
//    │     │ no │ no  │ no  │      no      │    no     │     │   │     │ 󰘶() │  no  │  no  │ 󰘶() │ no │     │
//    └─────┴────┼─────┼─────┼──────────────┼───────────┼─────┤   ├─────┼──────┼──────┼──────┼──────┼────┴─────┘
//               │     │     │              │           │     │   │     │      │      │      │      │
//               └─────┴─────┴──────────────┴───────────┴─────┘   └─────┴──────┴──────┴──────┴──────┘
[_RAISE] = LAYOUT(
  XXXXXXX , KC_VOLD , KC_VOLU , KC_MPRV , KC_MPLY                , KC_MNXT          ,                         XXXXXXX       , XXXXXXX , XXXXXXX , XXXXXXX        , XXXXXXX , KC_DEL ,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , LGUI(LSFT(LCTL(KC_4))) , LGUI(LSFT(KC_4)) ,                         KC_HOME       , KC_PGDN , KC_PGUP , KC_END         , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_ESC                 , XXXXXXX          ,                         KC_LEFT       , KC_DOWN , KC_UP   , KC_RIGHT       , XXXXXXX , XXXXXXX,
  _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX                , XXXXXXX          , _______ ,     _______ , LSFT(KC_LEFT) , XXXXXXX , XXXXXXX , LSFT(KC_RIGHT) , XXXXXXX , _______,
                      _______ , _______ , _______                , _______          , _______ ,     _______ , _______       , _______ , _______ , _______
),

//    ┌─────────┬─────────┬─────────┬─────────┬─────┬─────┐               ┌─────────┬─────┬─────┬────────────┬────┬────┐
//    │ EE_CLR  │   no    │   no    │   no    │ no  │ no  │               │   no    │ no  │ no  │     no     │ no │ no │
//    ├─────────┼─────────┼─────────┼─────────┼─────┼─────┤               ├─────────┼─────┼─────┼────────────┼────┼────┤
//    │ QK_BOOT │   no    │   no    │   no    │ no  │ no  │               │   no    │ no  │ no  │     no     │ no │ no │
//    ├─────────┼─────────┼─────────┼─────────┼─────┼─────┤               ├─────────┼─────┼─────┼────────────┼────┼────┤
//    │ RGB_TOG │ RGB_HUI │ RGB_SAI │ RGB_VAI │ no  │ no  │               │ C(G()) │ no  │ no  │ C(G(rght)) │ no │ no │
//    ├─────────┼─────────┼─────────┼─────────┼─────┼─────┼─────┐   ┌─────┼─────────┼─────┼─────┼────────────┼────┼────┤
//    │ RGB_MOD │ RGB_HUD │ RGB_SAD │ RGB_VAD │ no  │    │ no  │   │ no  │   no    │  󰒮  │    │     󰒭      │ no │ no │
//    └─────────┴─────────┼─────────┼─────────┼─────┼─────┼─────┤   ├─────┼─────────┼─────┼─────┼────────────┼────┴────┘
//                        │         │         │     │     │     │   │     │         │     │     │            │
//                        └─────────┴─────────┴─────┴─────┴─────┘   └─────┴─────────┴─────┴─────┴────────────┘
[_ADJUST] = LAYOUT(
  EE_CLR  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX   ,                         XXXXXXX       , XXXXXXX , XXXXXXX , XXXXXXX       , XXXXXXX , XXXXXXX,
  QK_BOOT , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX   ,                         XXXXXXX       , XXXXXXX , XXXXXXX , XXXXXXX       , XXXXXXX , XXXXXXX,
  RGB_TOG , RGB_HUI , RGB_SAI , RGB_VAI , XXXXXXX , XXXXXXX   ,                         C(G(KC_LEFT)) , KC_NO   , KC_NO   , C(G(KC_RGHT)) , XXXXXXX , XXXXXXX,
  RGB_MOD , RGB_HUD , RGB_SAD , RGB_VAD , XXXXXXX , KC_QWERTY , XXXXXXX ,     XXXXXXX , XXXXXXX       , KC_MPRV , KC_MPLY , KC_MNXT       , XXXXXXX , XXXXXXX,
                      _______ , _______ , _______ , _______   , _______ ,     _______ , _______       , _______ , _______ , _______
),

//    ┌─────┬────┬─────┬──────────────┬─────┬─────┐               ┌─────┬─────┬──────┬─────┬────┬─────┐
//    │     │ no │ no  │      no      │ no  │ no  │               │     │ nUM │  no  │ no  │ no │ no  │
//    ├─────┼────┼─────┼──────────────┼─────┼─────┤               ├─────┼─────┼──────┼─────┼────┼─────┤
//    │ no  │ no │ no  │      no      │ no  │ no  │               │  ^  │  7  │  8   │  9  │ *  │ no  │
//    ├─────┼────┼─────┼──────────────┼─────┼─────┤               ├─────┼─────┼──────┼─────┼────┼─────┤
//    │ no  │ no │ no  │      no      │ no  │ no  │               │  -  │  4  │  5   │  6  │ =  │  |  │
//    ├─────┼────┼─────┼──────────────┼─────┼─────┼─────┐   ┌─────┼─────┼─────┼──────┼─────┼────┼─────┤
//    │ no  │ no │ no  │      no      │ no  │ no  │     │   │     │  +  │  1  │  2   │  3  │ /  │     │
//    └─────┴────┼─────┼──────────────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼──────┼─────┼────┴─────┘
//               │     │ OSM(MOD_MEH) │     │     │     │   │     │     │  0  │ kp_. │     │
//               └─────┴──────────────┴─────┴─────┴─────┘   └─────┴─────┴─────┴──────┴─────┘
[_NUMPAD] = LAYOUT(
  _______ , XXXXXXX , XXXXXXX , XXXXXXX      , XXXXXXX , XXXXXXX ,                         _______ , KC_NUM , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX      , XXXXXXX , XXXXXXX ,                         KC_CIRC , KC_7   , KC_8    , KC_9    , KC_ASTR , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX      , XXXXXXX , XXXXXXX ,                         KC_MINS , KC_4   , KC_5    , KC_6    , KC_EQL  , KC_PIPE,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX      , XXXXXXX , XXXXXXX , _______ ,     _______ , KC_PLUS , KC_1   , KC_2    , KC_3    , KC_SLSH , _______,
                      _______ , OSM(MOD_MEH) , _______ , _______ , _______ ,     _______ , _______ , KC_0   , KC_PDOT , _______
)
};

#ifdef RGBLIGHT_ENABLE
char layer_state_str[70];
// Now define the array of layers. Later layers take precedence

// QWERTY,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_PURPLE)

);
const rgblight_segment_t PROGMEM layer_linux_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_GREEN)
);

// _NUM,
// Light on outer column and underglow
const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID(HSV_TEAL)
);
// _SYMBOL,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID(HSV_BLUE)

    );
// _COMMAND,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_RED)
);

//_NUMPAD
const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_INDICATORS(HSV_ORANGE),
    SET_UNDERGLOW(HSV_ORANGE),
	SET_NUMPAD(HSV_BLUE),
    {7, 4, HSV_ORANGE},
    {25, 2, HSV_ORANGE},
    {35+6, 4, HSV_ORANGE},
    {35+25, 2, HSV_ORANGE}
    );
// );

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_qwerty_lights,
    layer_linux_lights,
	layer_num_lights,// overrides layer 1
	layer_symbol_lights,
    layer_command_lights,
	layer_numpad_lights
);

layer_state_t layer_state_set_user(layer_state_t state) {
	rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_QWERTY));
	rgblight_set_layer_state(1, layer_state_cmp(state, _LINUX));
	rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
	rgblight_set_layer_state(3, layer_state_cmp(state, _RAISE));
	rgblight_set_layer_state(4, layer_state_cmp(state, _ADJUST));
	rgblight_set_layer_state(5, layer_state_cmp(state, _NUMPAD));
	// rgblight_set_layer_state(6, layer_state_cmp(state, _SWITCH));
    return state;
}
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

	rgblight_mode(10);// haven't found a way to set this in a more useful way

}
#endif

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("John\nEnd"), false);

    oled_write_ln_P(PSTR(""), false);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;

        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _LINUX:
            oled_write_P(PSTR("Linux\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adj\n"), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("Nump\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_LINUX:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_LINUX);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
    }
    return true;
}
