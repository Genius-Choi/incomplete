int uECC_curve_public_key_size(uECC_Curve curve) {
    return 2 * curve->num_bytes;
}
