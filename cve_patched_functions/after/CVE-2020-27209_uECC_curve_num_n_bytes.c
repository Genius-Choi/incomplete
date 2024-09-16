unsigned uECC_curve_num_n_bytes(uECC_Curve curve) {
    return BITS_TO_BYTES(curve->num_n_bits);
}
