uECC_VLI_API uECC_word_t uECC_vli_equal(const uECC_word_t *left,
                                        const uECC_word_t *right,
                                        wordcount_t num_words) {
    uECC_word_t diff = 0;
    wordcount_t i;
    for (i = num_words - 1; i >= 0; --i) {
        diff |= (left[i] ^ right[i]);
    }
    return (diff == 0);
}
