uECC_VLI_API int uECC_generate_random_int(uECC_word_t *random,
                                          const uECC_word_t *top,
                                          wordcount_t num_words) {
    uECC_word_t mask = (uECC_word_t)-1;
    uECC_word_t tries;
    bitcount_t num_bits = uECC_vli_numBits(top, num_words);

    if (!g_rng_function) {
        return 0;
    }

    for (tries = 0; tries < uECC_RNG_MAX_TRIES; ++tries) {
        if (!g_rng_function((uint8_t *)random, num_words * uECC_WORD_SIZE)) {
            return 0;
	    }
        random[num_words - 1] &= mask >> ((bitcount_t)(num_words * uECC_WORD_SIZE * 8 - num_bits));
        if (!uECC_vli_isZero(random, num_words) &&
		        uECC_vli_cmp(top, random, num_words) == 1) {
            return 1;
        }
    }
    return 0;
}
