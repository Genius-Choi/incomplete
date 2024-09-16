void uECC_vli_mod_sqrt(uECC_word_t *a, uECC_Curve curve) {
    curve->mod_sqrt(a, curve);
}
