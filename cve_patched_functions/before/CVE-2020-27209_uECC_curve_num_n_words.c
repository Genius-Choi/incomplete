unsigned uECC_curve_num_n_words(uECC_Curve curve) {
    return BITS_TO_WORDS(curve->num_n_bits);
}
