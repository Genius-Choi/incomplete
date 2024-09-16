void uECC_decompress(const uint8_t *compressed, uint8_t *public_key, uECC_Curve curve) {
#if uECC_VLI_NATIVE_LITTLE_ENDIAN
    uECC_word_t *point = (uECC_word_t *)public_key;
#else
    uECC_word_t point[uECC_MAX_WORDS * 2];
#endif
    uECC_word_t *y = point + curve->num_words;
#if uECC_VLI_NATIVE_LITTLE_ENDIAN
    bcopy(public_key, compressed+1, curve->num_bytes);
#else
    uECC_vli_bytesToNative(point, compressed + 1, curve->num_bytes);
#endif
    curve->x_side(y, point, curve);
    curve->mod_sqrt(y, curve);

    if ((y[0] & 0x01) != (compressed[0] & 0x01)) {
        uECC_vli_sub(y, curve->p, y, curve->num_words);
    }

#if uECC_VLI_NATIVE_LITTLE_ENDIAN == 0
    uECC_vli_nativeToBytes(public_key, curve->num_bytes, point);
    uECC_vli_nativeToBytes(public_key + curve->num_bytes, curve->num_bytes, y);
#endif
}
