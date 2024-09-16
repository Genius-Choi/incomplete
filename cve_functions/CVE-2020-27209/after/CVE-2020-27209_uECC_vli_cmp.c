uECC_VLI_API cmpresult_t uECC_vli_cmp(const uECC_word_t *left,
                                      const uECC_word_t *right,
                                      wordcount_t num_words) {
    uECC_word_t tmp[uECC_MAX_WORDS];
    uECC_word_t neg = !!uECC_vli_sub(tmp, left, right, num_words);
    uECC_word_t equal = uECC_vli_isZero(tmp, num_words);
    return (!equal - 2 * neg);
}
