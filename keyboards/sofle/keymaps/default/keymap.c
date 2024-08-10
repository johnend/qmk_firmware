// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    KC_QWERTY = QK_USER,
    KC_COLEMAK,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌──────┬───┬──────┬──────┬──────┬─────────┐                ┌─────────┬──────┬──────┬──────┬───┬──────┐
//    │  `   │ 1 │  2   │  3   │  4   │    5    │                │    6    │  7   │  8   │  9   │ 0 │  `   │
//    ├──────┼───┼──────┼──────┼──────┼─────────┤                ├─────────┼──────┼──────┼──────┼───┼──────┤
//    │ esc  │ q │  w   │  e   │  r   │    t    │                │    y    │  u   │  i   │  o   │ p │ bspc │
//    ├──────┼───┼──────┼──────┼──────┼─────────┤                ├─────────┼──────┼──────┼──────┼───┼──────┤
//    │ tab  │ a │  s   │  d   │  f   │    g    │                │    h    │  j   │  k   │  l   │ ; │  '   │
//    ├──────┼───┼──────┼──────┼──────┼─────────┼──────┐   ┌─────┼─────────┼──────┼──────┼──────┼───┼──────┤
//    │ lsft │ z │  x   │  c   │  v   │    b    │ mute │   │ no  │    n    │  m   │  ,   │  .   │ / │ rsft │
//    └──────┴───┼──────┼──────┼──────┼─────────┼──────┤   ├─────┼─────────┼──────┼──────┼──────┼───┴──────┘
//               │ lgui │ lalt │ lctl │ TL_LOWR │ ent  │   │ spc │ TL_UPPR │ rctl │ ralt │ rgui │           
//               └──────┴──────┴──────┴─────────┴──────┘   └─────┴─────────┴──────┴──────┴──────┘           
[_QWERTY] = LAYOUT(
  KC_GRV  , KC_1 , KC_2    , KC_3    , KC_4    , KC_5    ,                         KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_GRV ,
  KC_ESC  , KC_Q , KC_W    , KC_E    , KC_R    , KC_T    ,                         KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC,
  KC_TAB  , KC_A , KC_S    , KC_D    , KC_F    , KC_G    ,                         KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT,
  KC_LSFT , KC_Z , KC_X    , KC_C    , KC_V    , KC_B    , KC_MUTE ,     XXXXXXX , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT,
                   KC_LGUI , KC_LALT , KC_LCTL , TL_LOWR , KC_ENT  ,     KC_SPC  , TL_UPPR , KC_RCTL , KC_RALT , KC_RGUI                    
),

//    ┌──────┬───┬──────┬──────┬──────┬─────────┐                ┌─────────┬──────┬──────┬──────┬───┬──────┐
//    │  `   │ 1 │  2   │  3   │  4   │    5    │                │    6    │  7   │  8   │  9   │ 0 │  `   │
//    ├──────┼───┼──────┼──────┼──────┼─────────┤                ├─────────┼──────┼──────┼──────┼───┼──────┤
//    │ esc  │ q │  w   │  f   │  p   │    g    │                │    j    │  l   │  u   │  y   │ ; │ bspc │
//    ├──────┼───┼──────┼──────┼──────┼─────────┤                ├─────────┼──────┼──────┼──────┼───┼──────┤
//    │ tab  │ a │  r   │  s   │  t   │    d    │                │    h    │  n   │  e   │  i   │ o │  '   │
//    ├──────┼───┼──────┼──────┼──────┼─────────┼──────┐   ┌─────┼─────────┼──────┼──────┼──────┼───┼──────┤
//    │ lsft │ z │  x   │  c   │  v   │    b    │ mute │   │ no  │    k    │  m   │  ,   │  .   │ / │ rsft │
//    └──────┴───┼──────┼──────┼──────┼─────────┼──────┤   ├─────┼─────────┼──────┼──────┼──────┼───┴──────┘
//               │ lgui │ lalt │ lctl │ TL_LOWR │ ent  │   │ spc │ TL_UPPR │ rctl │ ralt │ rgui │           
//               └──────┴──────┴──────┴─────────┴──────┘   └─────┴─────────┴──────┴──────┴──────┘           
[_COLEMAK] = LAYOUT(
  KC_GRV  , KC_1 , KC_2    , KC_3    , KC_4    , KC_5    ,                         KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_GRV ,
  KC_ESC  , KC_Q , KC_W    , KC_F    , KC_P    , KC_G    ,                         KC_J    , KC_L    , KC_U    , KC_Y    , KC_SCLN , KC_BSPC,
  KC_TAB  , KC_A , KC_R    , KC_S    , KC_T    , KC_D    ,                         KC_H    , KC_N    , KC_E    , KC_I    , KC_O    , KC_QUOT,
  KC_LSFT , KC_Z , KC_X    , KC_C    , KC_V    , KC_B    , KC_MUTE ,     XXXXXXX , KC_K    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT,
                   KC_LGUI , KC_LALT , KC_LCTL , TL_LOWR , KC_ENT  ,     KC_SPC  , TL_UPPR , KC_RCTL , KC_RALT , KC_RGUI                    
),

//    ┌─────┬────┬─────┬─────┬─────┬─────┐               ┌─────┬─────┬─────┬─────┬─────┬─────┐
//    │     │ f1 │ f2  │ f3  │ f4  │ f5  │               │ f6  │ f7  │ f8  │ f9  │ f10 │ f11 │
//    ├─────┼────┼─────┼─────┼─────┼─────┤               ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │  `  │ 1  │  2  │  3  │  4  │  5  │               │  6  │  7  │  8  │  9  │  0  │ f12 │
//    ├─────┼────┼─────┼─────┼─────┼─────┤               ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │ !  │  @  │  #  │  $  │  %  │               │  ^  │  &  │  *  │  (  │  )  │  |  │
//    ├─────┼────┼─────┼─────┼─────┼─────┼─────┐   ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │ =  │  -  │  +  │  {  │  }  │     │   │     │  [  │  ]  │  ;  │  :  │  \  │     │
//    └─────┴────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┴─────┘
//               │     │     │     │     │     │   │     │     │     │     │     │            
//               └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘            
[_LOWER] = LAYOUT(
  _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                         KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11 ,
  KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                         KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_F12 ,
  _______ , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC ,                         KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_PIPE,
  _______ , KC_EQL  , KC_MINS , KC_PLUS , KC_LCBR , KC_RCBR , _______ ,     _______ , KC_LBRC , KC_RBRC , KC_SCLN , KC_COLN , KC_BSLS , _______,
                      _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______                    
),

//    ┌─────┬──────┬──────┬──────┬──────┬──────┐               ┌──────┬───────┬──────┬───────┬─────────┬──────┐
//    │     │      │      │      │      │      │               │      │       │      │       │         │      │
//    ├─────┼──────┼──────┼──────┼──────┼──────┤               ├──────┼───────┼──────┼───────┼─────────┼──────┤
//    │     │ ins  │ pscr │ app  │  no  │  no  │               │ pgup │ pRVWD │  up  │ nXTWD │ C(bspc) │ bspc │
//    ├─────┼──────┼──────┼──────┼──────┼──────┤               ├──────┼───────┼──────┼───────┼─────────┼──────┤
//    │     │ lalt │ lctl │ lsft │  no  │ caps │               │ pgdn │ left  │ down │ rght  │   del   │ bspc │
//    ├─────┼──────┼──────┼──────┼──────┼──────┼─────┐   ┌─────┼──────┼───────┼──────┼───────┼─────────┼──────┤
//    │     │ C(z) │ C(x) │ C(c) │ C(v) │  no  │     │   │     │  no  │ lSTRT │  no  │ lEND  │   no    │      │
//    └─────┴──────┼──────┼──────┼──────┼──────┼─────┤   ├─────┼──────┼───────┼──────┼───────┼─────────┴──────┘
//                 │      │      │      │      │     │   │     │      │       │      │       │                 
//                 └──────┴──────┴──────┴──────┴─────┘   └─────┴──────┴───────┴──────┴───────┘                 
[_RAISE] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______ ,                         _______ , _______  , _______ , _______  , _______    , _______,
  _______ , KC_INS  , KC_PSCR , KC_APP  , XXXXXXX , XXXXXXX ,                         KC_PGUP , KC_PRVWD , KC_UP   , KC_NXTWD , C(KC_BSPC) , KC_BSPC,
  _______ , KC_LALT , KC_LCTL , KC_LSFT , XXXXXXX , KC_CAPS ,                         KC_PGDN , KC_LEFT  , KC_DOWN , KC_RGHT  , KC_DEL     , KC_BSPC,
  _______ , C(KC_Z) , C(KC_X) , C(KC_C) , C(KC_V) , XXXXXXX , _______ ,     _______ , XXXXXXX , KC_LSTRT , XXXXXXX , KC_LEND  , XXXXXXX    , _______,
                      _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______  , _______ , _______                        
),

//    ┌─────────┬────┬─────────┬─────────┬─────────┬─────┐               ┌─────┬──────┬──────┬──────┬────┬────┐
//    │   no    │ no │   no    │   no    │   no    │ no  │               │ no  │  no  │  no  │  no  │ no │ no │
//    ├─────────┼────┼─────────┼─────────┼─────────┼─────┤               ├─────┼──────┼──────┼──────┼────┼────┤
//    │ QK_BOOT │ no │ qWERTY  │ cOLEMAK │ CG_TOGG │ no  │               │ no  │  no  │  no  │  no  │ no │ no │
//    ├─────────┼────┼─────────┼─────────┼─────────┼─────┤               ├─────┼──────┼──────┼──────┼────┼────┤
//    │   no    │ no │ CG_TOGG │   no    │   no    │ no  │               │ no  │ vold │ mute │ volu │ no │ no │
//    ├─────────┼────┼─────────┼─────────┼─────────┼─────┼─────┐   ┌─────┼─────┼──────┼──────┼──────┼────┼────┤
//    │   no    │ no │   no    │   no    │   no    │ no  │ no  │   │ no  │ no  │ mprv │ mply │ mnxt │ no │ no │
//    └─────────┴────┼─────────┼─────────┼─────────┼─────┼─────┤   ├─────┼─────┼──────┼──────┼──────┼────┴────┘
//                   │         │         │         │     │     │   │     │     │      │      │      │          
//                   └─────────┴─────────┴─────────┴─────┴─────┘   └─────┴─────┴──────┴──────┴──────┘          
[_ADJUST] = LAYOUT(
  XXXXXXX , XXXXXXX , XXXXXXX   , XXXXXXX    , XXXXXXX , XXXXXXX ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  QK_BOOT , XXXXXXX , KC_QWERTY , KC_COLEMAK , CG_TOGG , XXXXXXX ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , CG_TOGG   , XXXXXXX    , XXXXXXX , XXXXXXX ,                         XXXXXXX , KC_VOLD , KC_MUTE , KC_VOLU , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX   , XXXXXXX    , XXXXXXX , XXXXXXX , XXXXXXX ,     XXXXXXX , XXXXXXX , KC_MPRV , KC_MPLY , KC_MNXT , XXXXXXX , XXXXXXX,
                      _______   , _______    , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______                    
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                     //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
    }
    return true;
}
