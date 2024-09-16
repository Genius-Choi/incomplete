static enum test_return cache_fail_constructor_test(void)
{
    enum test_return ret = TEST_PASS;

    cache_t *cache = cache_create("test", sizeof(uint64_t), sizeof(uint64_t),
                                  cache_fail_constructor, NULL);
    assert(cache != NULL);
    uint64_t *ptr = cache_alloc(cache);
    if (ptr != NULL) {
        ret = TEST_FAIL;
    }
    cache_destroy(cache);
    return ret;
}
