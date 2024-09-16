uECC_VLI_API void uECC_vli_square(uECC_word_t *result,
                                  const uECC_word_t *left,
                                  wordcount_t num_words) {
    uECC_vli_mult(result, left, left, num_words);
}
