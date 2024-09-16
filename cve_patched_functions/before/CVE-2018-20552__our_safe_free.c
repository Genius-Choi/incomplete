_our_safe_free(void *ptr, const char *funcname, const int line, const char *file)
{
    assert(funcname);
    assert(line);
    assert(file);

    if (ptr == NULL)
        return;

    free(ptr);
}
