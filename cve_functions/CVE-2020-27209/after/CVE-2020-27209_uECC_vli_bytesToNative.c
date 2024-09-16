uECC_VLI_API void uECC_vli_bytesToNative(uECC_word_t *native,
                                         const uint8_t *bytes,
                                         int num_bytes) {
    wordcount_t i;
    uECC_vli_clear(native, (num_bytes + (uECC_WORD_SIZE - 1)) / uECC_WORD_SIZE);
    for (i = 0; i < num_bytes; ++i) {
        unsigned b = num_bytes - 1 - i;
        native[b / uECC_WORD_SIZE] |=
            (uECC_word_t)bytes[i] << (8 * (b % uECC_WORD_SIZE));
    }
}
