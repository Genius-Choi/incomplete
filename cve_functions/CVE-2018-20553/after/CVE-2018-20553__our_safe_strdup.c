_our_safe_strdup(const char *str, const char *funcname, const int line, const char *file)
{
    char *newstr;

    if ((newstr = (char *)malloc(strlen(str) + 1)) == NULL) {
        fprintf(stderr, "ERROR in %s:%s() line %d: Unable to strdup() %zu bytes\n", file, funcname, line, strlen(str));
        exit(-1);
    }

    memcpy(newstr, str, strlen(str) + 1);

    return newstr;

}
