_our_safe_realloc(void *ptr, size_t len, const char *funcname, const int line, const char *file)
{

    if ((ptr = realloc(ptr, len)) == NULL) {
        fprintf(stderr, "ERROR: in %s:%s() line %d: Unable to remalloc() buffer to %zu bytes", file, funcname, line, len);
        exit(-1);
    }

    dbgx(5, "Remalloc'd buffer to %zu bytes in %s:%s() line %d", len, file, funcname, line);

    return ptr;
}
