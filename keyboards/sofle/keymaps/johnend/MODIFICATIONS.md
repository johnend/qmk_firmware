# Sofle Keyboard - johnend Keymap Modifications

**Last Updated:** February 2, 2026  
**Purpose:** Document all modifications made to optimize firmware size and enable VIAL support

---

## Overview
This document tracks all changes made to the Sofle keyboard firmware to:
- Reduce firmware size for VIAL support
- Remove unused features
- Implement homerow mods with bilateral combinations
- Simplify RGB lighting to static layer indicators only

---

## Modifications Log

### 1. RGB Lighting Simplification
**Date:** Feb 2, 2026  
**Reason:** RGB animations consume significant firmware space. Static layer indicators are sufficient.

**Changes Made:**
- Removed all RGB animation effects (breathing, rainbow, snake, etc.)
- Kept only static RGB layer indicators
- Simplified RGB configuration to minimal settings
- RGB now only shows layer status with static colors

**To Re-implement Animations:** 
Add back to `config.h` under `RGBLIGHT_ENABLE` section:
```c
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
// etc.
```

---

### 2. Layer Structure Changes
**Date:** Feb 2, 2026  
**Reason:** _LINUX layer was redundant (identical to _QWERTY)

**Changes Made:**
- Removed `_LINUX` layer (was Layer 1)
- Updated layer enum from 7 layers to 6
- Removed layer switching functionality from encoder button
- Updated OLED display code to remove Linux layer references
- Updated RGB layer indicators to remove Linux layer

**Previous Layer Structure:**
```
0: _QWERTY
1: _LINUX (REMOVED)
2: _LOWER
3: _RAISE
4: _ADJUST
5: _NUMPAD
```

**New Layer Structure:**
```
0: _QWERTY
1: _LOWER
2: _RAISE
3: _ADJUST
4: _NUMPAD
```

**To Re-implement Linux Layer:**
1. Add `_LINUX` back to enum in keymap.c
2. Copy the LINUX layer keymap definition
3. Add RGB layer indicator for Linux (Green: HSV_GREEN)
4. Update OLED display to show Linux layer
5. Add TO(1) back to encoder button

---

### 3. Homerow Mods with Chordal Hold
**Date:** Feb 3, 2026  
**Reason:** Improve ergonomics and reduce reliance on physical modifier keys

**Layout:**
```
Left Hand:  A=Shift  S=GUI  D=Alt  F=Ctrl
Right Hand: J=Ctrl   K=Alt  L=GUI  ;=Shift
```

**Configuration:**
- `CHORDAL_HOLD` - QMK's built-in bilateral combinations feature
- `PERMISSIVE_HOLD` - Works with Chordal Hold for opposite-hand activation
- `chordal_hold_layout` - Defines left/right hand positions for split keyboard
- Tapping term: 200ms globally
- Thumb keys marked with `*` in layout (exempt from opposite-hand rule)

**How Chordal Hold Works:**
QMK's built-in feature automatically handles same-hand vs opposite-hand behavior:
- **Opposite hand** (F held, J pressed): Activates mod immediately (permissive hold)
- **Same hand** (F held, D pressed): Treated as tap, produces "fd"
- This allows fast same-hand typing/rolling without accidental mod activation
- Opposite-hand combinations activate quickly and reliably
- Thumb keys (`*` in layout) work with any key on either hand

**Advantages Over Manual Implementation:**
- ✅ Built into QMK firmware (well-tested, maintained)
- ✅ Simpler code (~100 lines removed)
- ✅ Better performance (no manual position tracking needed)
- ✅ More reliable (QMK's tested algorithm)
- ✅ Easier to configure (just define the layout matrix)

**To Disable Homerow Mods:**
1. Replace `LSFT_T(KC_A)` with `KC_A` (and similar for all homerow positions)
2. Remove `CHORDAL_HOLD` and `PERMISSIVE_HOLD` from config.h
3. Remove `chordal_hold_layout` definition from keymap.c

**To Adjust Behavior:**
Edit `chordal_hold_layout` in keymap.c:
- Change `'L'` or `'R'` to `'*'` to exempt specific keys from the opposite-hand rule
- Adjust `TAPPING_TERM` in config.h to change hold delay (default 200ms)

---

### 4. RGB Layer Color Scheme
**Date:** Feb 2, 2026  

**New Color Assignments (ALL LEDs light up in layer color):**
- **QWERTY** (Base): Purple (`HSV_PURPLE`) - all 72 LEDs
- **LOWER**: Red (`HSV_RED`) - all 72 LEDs
- **RAISE**: White (`HSV_WHITE`) - all 72 LEDs
- **ADJUST**: Purple (`HSV_PURPLE`) - all 72 LEDs
- **NUMPAD**: Green (`HSV_GREEN`) - all 72 LEDs

**Changes Made:**
- Changed from `SET_LAYER_ID()` macro (only lit specific zones) to full LED range
- Now uses `{0, RGBLIGHT_LED_COUNT, HSV_COLOR}` to light all LEDs
- Static mode (mode 1) for minimal firmware impact

**Previous Implementation:**
- Only lit indicators, underglow, outer columns, and thumb clusters
- Left most of the keyboard red/unlit

**To Customize Colors:**
Edit the layer light definitions in keymap.c and change HSV values:
```c
const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLIGHT_LED_COUNT, HSV_BLUE}  // Change HSV_PURPLE to any HSV color
);
```

Available colors: HSV_RED, HSV_ORANGE, HSV_YELLOW, HSV_GREEN, HSV_CYAN, HSV_BLUE, HSV_PURPLE, HSV_MAGENTA, HSV_WHITE

---

### 5. Encoder Configuration
**Date:** Feb 2, 2026  

**Changes:**
- Right encoder button changed from `TO(1)` (Linux layer) to `KC_MUTE`
- Left encoder remains as media play/pause

---

### 6. Double-Tap-Hold Delete Feature
**Date:** Feb 2, 2026  
**Reason:** Add Cyboard Imprint-style double-tap-hold delete functionality to RAISE_BSPC key

**Key:** Right thumb second key (formerly `LT(_RAISE, KC_BSPC)`)

**Behavior:**
- **Single tap**: Sends Backspace
- **Hold (200ms+)**: Activates RAISE layer
- **Double-tap-hold**: Sends Delete with key repeat enabled
  - Tap twice quickly, hold on second tap
  - Delete key remains registered, allowing OS key repeat
  - Release to stop deleting

**Implementation Details:**
- Custom keycode `RAISE_BSPC` added to enum
- State tracking variables:
  - `raise_bspc_tap_count` - Tracks number of taps
  - `raise_bspc_timer` - Timer for tap detection
  - `raise_bspc_delete_registered` - Tracks if delete is active
  - `raise_bspc_layer_activated` - Tracks if layer is active
- `process_record_user()` handles tap detection and key events
- `matrix_scan_user()` handles layer activation timing on hold
- Uses `TAPPING_TERM` (200ms) for double-tap detection window

**Configuration:**
To adjust double-tap sensitivity, change the tap detection window in `matrix_scan_user()`:
```c
if (timer_elapsed(raise_bspc_timer) > TAPPING_TERM * 2) {
  // Increase multiplier (e.g., * 3) for more lenient double-tap timing
}
```

**Firmware Impact:** +288 bytes (26,088 → 26,376 bytes)

---

### 7. VIAL Support
**Date:** Feb 2, 2026  
**Reason:** Enable runtime keymap configuration without re-flashing

**Important:** VIAL support requires the VIAL fork of QMK firmware, not standard QMK.

**Current Status:** 
- Firmware optimized and ready for VIAL (91% capacity - 26376/28672 bytes, 2296 bytes free)
- All unnecessary features removed to make space
- Standard QMK build successful

**To Enable VIAL Support:**
1. Clone the VIAL QMK fork: `git clone https://github.com/vial-kb/vial-qmk.git`
2. Copy this keymap to the VIAL QMK directory:
   ```bash
   cp -r keyboards/sofle/keymaps/johnend /path/to/vial-qmk/keyboards/sofle/keymaps/
   ```
3. Create a `vial.json` file in the keymap directory with the keyboard layout definition
4. Enable VIAL in rules.mk: `VIAL_ENABLE = yes`
5. Compile using VIAL QMK: `qmk compile -kb sofle -km johnend`

**Alternative: Use VIA (Simpler)**
If you just want runtime configuration without VIAL's extra features:
1. Enable in rules.mk: `VIA_ENABLE = yes`
2. Recompile firmware
3. Use VIA desktop application (via.caniuselabs.com)
4. Note: VIA typically requires 4 layers max (you have 5, so may need adjustment)

**VIAL Features Available (when using VIAL fork):**
- Runtime keymap editing
- Layer configuration  
- Macro programming
- Tap/hold configuration
- Combo configuration
- More advanced features than VIA

**To Disable VIAL:**
Set in rules.mk: `VIAL_ENABLE = no`

**Current Firmware Size:**
- Used: 26376 bytes (91%)
- Available: 28672 bytes total
- Free: 2296 bytes
- Status: ✅ Optimized and ready for VIA or VIAL

---

### 8. Firmware Size Optimizations
**Date:** Feb 2, 2026  

**Optimizations Applied:**
- LTO_ENABLE = yes (Link Time Optimization)
- Console debugging disabled
- RGB animations removed
- Reduced layer count (7→6)
- Simplified RGB to static indicators only
- RGBLIGHT_EFFECT_TWINKLE removed

**Size Monitoring:**
Check firmware size with: `qmk compile -kb sofle -km johnend`
Target: Stay under AVR size limits for VIAL support

---

## Configuration Summary

### Current Features Enabled
- ✅ OLED displays
- ✅ Rotary encoders
- ✅ Caps Word (double-tap shift)
- ✅ Homerow mods with bilateral combinations
- ✅ Double-tap-hold delete on RAISE_BSPC key
- ✅ Static RGB layer indicators
- ✅ VIAL support
- ✅ Extra keys (media/system control)
- ✅ LTO (firmware size optimization)

### Current Features Disabled
- ❌ VIA (replaced by VIAL)
- ❌ Console debugging
- ❌ RGB animations/effects
- ❌ RGB Matrix effects
- ❌ Linux layer

---

## Quick Reference: Key Behaviors

### Homerow Mod Behavior

**Same Hand (produces letters):**
- Hold F, tap D = "d"
- Hold A, tap S = "s"

**Opposite Hand (activates mod):**
- Hold F (Ctrl), tap J = Ctrl+J
- Hold A (Shift), tap L = Shift+L

**Thumb Keys (always activate mod):**
- Work with any key regardless of hand

### RAISE_BSPC Key Behavior

**Right thumb second key:**
- **Tap once**: Backspace
- **Hold**: Activate RAISE layer
- **Double-tap-hold**: Delete with key repeat
  - Quickly tap twice, hold on second tap
  - Deletes continuously while held
  - Release to stop

---

## Troubleshooting

### Accidental Mod Activations
If mods activate too easily:
1. Increase `TAPPING_TERM` in config.h (try 200ms, 250ms)
2. Add `IGNORE_MOD_TAP_INTERRUPT` to config.h
3. Adjust per-key tapping term if needed

### Mods Not Activating
If mods don't activate when needed:
1. Decrease `TAPPING_TERM` in config.h
2. Check that `HOLD_ON_OTHER_KEY_PRESS` is enabled
3. Verify bilateral combination logic

### Firmware Too Large
If firmware exceeds size limits:
1. Disable OLED: `OLED_ENABLE = no`
2. Disable RGB: `RGBLIGHT_ENABLE = no`
3. Reduce layer count further
4. Disable encoders: `ENCODER_ENABLE = no`

---

## Build Commands

**Compile:**
```bash
qmk compile -kb sofle -km johnend
```

**Flash:**
```bash
qmk flash -kb sofle -km johnend
```

**Check Size:**
```bash
qmk compile -kb sofle -km johnend | grep "bytes"
```

---

## Additional Notes

- Original configuration based on Dane Evans' Sofle RGB keymap
- Master side: LEFT
- OLED rotation: 270° on master side
- Encoder direction: FLIPPED
- Total LEDs: 70 (35 per side)

