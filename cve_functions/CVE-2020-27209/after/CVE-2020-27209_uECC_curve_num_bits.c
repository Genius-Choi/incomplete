unsigned uECC_curve_num_bits(uECC_Curve curve) {
    return curve->num_bytes * 8;
}
