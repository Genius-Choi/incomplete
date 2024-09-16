static int unloadMem(const char *mem) {
    free((char *)mem);
    return(0);
}
