RGB_MATRIX_EFFECT(shortcuts)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool shortcuts(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);

    switch(get_highest_layer(layer_state|default_layer_state)) {
        case 2:
            for (uint8_t i = led_min; i < led_max; i++) {
                if(i == 34) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                } else {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
            break;
        default:
            for (uint8_t i = led_min; i < led_max; i++) {
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
            break;
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
