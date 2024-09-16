static int loadMem(const char *filename, const char **mem, int *size) {
    int fd, res;
    struct stat info;
    char *base;
    int siz = 0;
    if (stat(filename, &info) < 0)
	return(-1);
    base = malloc(info.st_size + 1);
    if (base == NULL)
	return(-1);
    if ((fd = open(filename, RD_FLAGS)) < 0) {
        free(base);
	return(-1);
    }
    while ((res = read(fd, &base[siz], info.st_size - siz)) > 0) {
        siz += res;
    }
    close(fd);
#if !defined(_WIN32)
    if (siz != info.st_size) {
        free(base);
	return(-1);
    }
#endif
    base[siz] = 0;
    *mem = base;
    *size = siz;
    return(0);
}
