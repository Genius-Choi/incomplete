static int cache_constructor(void *buffer, void *notused1, int notused2) {
    uint64_t *ptr = buffer;
    *ptr = constructor_pattern;
    return 0;
}
