int uECC_make_key(uint8_t *public_key,
                  uint8_t *private_key,
                  uECC_Curve curve) {
#if uECC_VLI_NATIVE_LITTLE_ENDIAN
    uECC_word_t *_private = (uECC_word_t *)private_key;
    uECC_word_t *_public = (uECC_word_t *)public_key;
#else
    uECC_word_t _private[uECC_MAX_WORDS];
    uECC_word_t _public[uECC_MAX_WORDS * 2];
#endif
    uECC_word_t tries;

    for (tries = 0; tries < uECC_RNG_MAX_TRIES; ++tries) {
        if (!uECC_generate_random_int(_private, curve->n, BITS_TO_WORDS(curve->num_n_bits))) {
            return 0;
        }

        if (EccPoint_compute_public_key(_public, _private, curve)) {
#if uECC_VLI_NATIVE_LITTLE_ENDIAN == 0
            uECC_vli_nativeToBytes(private_key, BITS_TO_BYTES(curve->num_n_bits), _private);
            uECC_vli_nativeToBytes(public_key, curve->num_bytes, _public);
            uECC_vli_nativeToBytes(
                public_key + curve->num_bytes, curve->num_bytes, _public + curve->num_words);
#endif
            return 1;
        }
    }
    return 0;
}
