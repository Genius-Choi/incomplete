uECC_VLI_API void uECC_vli_modMult_fast(uECC_word_t *result,
                                        const uECC_word_t *left,
                                        const uECC_word_t *right,
                                        uECC_Curve curve) {
    uECC_word_t product[2 * uECC_MAX_WORDS];
    uECC_vli_mult(product, left, right, curve->num_words);
#if (uECC_OPTIMIZATION_LEVEL > 0)
    curve->mmod_fast(result, product);
#else
    uECC_vli_mmod(result, product, curve->p, curve->num_words);
#endif
}
