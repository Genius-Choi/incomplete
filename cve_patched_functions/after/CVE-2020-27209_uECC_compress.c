void uECC_compress(const uint8_t *public_key, uint8_t *compressed, uECC_Curve curve) {
    wordcount_t i;
    for (i = 0; i < curve->num_bytes; ++i) {
        compressed[i+1] = public_key[i];
    }
#if uECC_VLI_NATIVE_LITTLE_ENDIAN
    compressed[0] = 2 + (public_key[curve->num_bytes] & 0x01);
#else
    compressed[0] = 2 + (public_key[curve->num_bytes * 2 - 1] & 0x01);
#endif
}
