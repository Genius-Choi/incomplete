int uECC_curve_private_key_size(uECC_Curve curve) {
    return BITS_TO_BYTES(curve->num_n_bits);
}
