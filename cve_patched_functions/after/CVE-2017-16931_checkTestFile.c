static int checkTestFile(const char *filename) {
    struct stat buf;

    if (stat(filename, &buf) == -1)
        return(0);

#if defined(_WIN32) && !defined(__CYGWIN__)
    if (!(buf.st_mode & _S_IFREG))
        return(0);
#else
    if (!S_ISREG(buf.st_mode))
        return(0);
#endif

    return(1);
}
