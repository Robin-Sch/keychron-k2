// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(homerow_mods)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// e.g: A simple effect, self-contained within a single method
static bool homerow_mods(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  rgb_matrix_set_color_all(0, 0, 0);

  // Ctrl group – blue
  rgb_matrix_set_color(50, 0, 0, 96);  // F
  rgb_matrix_set_color(53, 0, 0, 96);  // J
  rgb_matrix_set_color(74, 0, 0, 96);  // LCtrl
  rgb_matrix_set_color(80, 0, 0, 96);  // RCtrl

  // Shift group – green
  rgb_matrix_set_color(49, 0, 96, 0);  // D
  rgb_matrix_set_color(54, 0, 96, 0);  // K
  rgb_matrix_set_color(60, 0, 96, 0);  // LShift
  rgb_matrix_set_color(71, 0, 96, 0);  // RShift

  // Alt group – red
  rgb_matrix_set_color(48, 96, 0, 0);  // S
  rgb_matrix_set_color(55, 96, 0, 0);  // L
  rgb_matrix_set_color(76, 96, 0, 0);  // LAlt
  rgb_matrix_set_color(78, 96, 0, 0);  // RAlt

  // GUI group – yellow
  rgb_matrix_set_color(47, 96, 0, 96); // A
  rgb_matrix_set_color(56, 96, 0, 96); // ;
  rgb_matrix_set_color(75, 96, 0, 96); // LGUI
  //rgb_matrix_set_color(, 96, 0, 96); // RGUI

  return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS