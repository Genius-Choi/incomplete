uECC_VLI_API void uECC_vli_modSquare(uECC_word_t *result,
                                     const uECC_word_t *left,
                                     const uECC_word_t *mod,
                                     wordcount_t num_words) {
    uECC_vli_modMult(result, left, left, mod, num_words);
}
