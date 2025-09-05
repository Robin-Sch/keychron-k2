// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(homerow_mods)
RGB_MATRIX_EFFECT(typing_heatmap_custom)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Animation: homerow mods
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

// Animation: custom homerow mods
#        ifndef RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS
#            define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 25
#        endif

// A timer to track the last time we decremented all heatmap values.
static uint16_t heatmap_decrease_timer;
// Whether we should decrement the heatmap values during the next update.
static bool decrease_heatmap_values;

bool typing_heatmap_custom(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  if (params->init) {
    rgb_matrix_set_color_all(255, 255, 255);
    memset(g_rgb_frame_buffer, 0, sizeof g_rgb_frame_buffer);
  }

  // The heatmap animation might run in several iterations depending on
  // `RGB_MATRIX_LED_PROCESS_LIMIT`, therefore we only want to update the
  // timer when the animation starts.
  if (params->iter == 0) {
    decrease_heatmap_values = timer_elapsed(heatmap_decrease_timer) >= RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS;

    // Restart the timer if we are going to decrease the heatmap this frame.
    if (decrease_heatmap_values) {
      heatmap_decrease_timer = timer_read();
    }
  }

  // Render heatmap & decrease
  uint8_t count = 0;
  for (uint8_t row = 0; row < MATRIX_ROWS && count < RGB_MATRIX_LED_PROCESS_LIMIT; row++) {
    for (uint8_t col = 0; col < MATRIX_COLS && RGB_MATRIX_LED_PROCESS_LIMIT; col++) {
      if (g_led_config.matrix_co[row][col] >= led_min && g_led_config.matrix_co[row][col] < led_max) {
        count++;
        uint8_t val = g_rgb_frame_buffer[row][col];
        if (!HAS_ANY_FLAGS(g_led_config.flags[g_led_config.matrix_co[row][col]], params->flags)) continue;

        if (val == 0) {
          rgb_matrix_set_color(g_led_config.matrix_co[row][col], 10, 15, 20);
        } else {
          hsv_t hsv = {170 - qsub8(val, 85), rgb_matrix_config.hsv.s, scale8((qadd8(170, val) - 170) * 3, rgb_matrix_config.hsv.v)};
          rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
          rgb_matrix_set_color(g_led_config.matrix_co[row][col], rgb.r, rgb.g, rgb.b);

          if (decrease_heatmap_values) {
            g_rgb_frame_buffer[row][col] = qsub8(val, 1);
          }
        }
      }
    }
  }

  return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS