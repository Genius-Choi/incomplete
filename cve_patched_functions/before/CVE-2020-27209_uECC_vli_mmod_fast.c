void uECC_vli_mmod_fast(uECC_word_t *result, uECC_word_t *product, uECC_Curve curve) {
#if (uECC_OPTIMIZATION_LEVEL > 0)
    curve->mmod_fast(result, product);
#else
    uECC_vli_mmod(result, product, curve->p, curve->num_words);
#endif
}
