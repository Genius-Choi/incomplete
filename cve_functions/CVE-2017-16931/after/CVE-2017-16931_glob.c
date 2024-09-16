static int glob(const char *pattern, int flags,
                int errfunc(const char *epath, int eerrno),
                glob_t *pglob) {
    glob_t *ret;
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    unsigned int nb_paths = 0;
    char directory[500];
    int len;

    if ((pattern == NULL) || (pglob == NULL)) return(-1);

    strncpy(directory, pattern, 499);
    for (len = strlen(directory);len >= 0;len--) {
        if (directory[len] == '/') {
	    len++;
	    directory[len] = 0;
	    break;
	}
    }
    if (len <= 0)
        len = 0;


    ret = pglob;
    memset(ret, 0, sizeof(glob_t));

    hFind = FindFirstFileA(pattern, &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE)
        return(0);
    nb_paths = 20;
    ret->gl_pathv = (char **) malloc(nb_paths * sizeof(char *));
    if (ret->gl_pathv == NULL) {
	FindClose(hFind);
        return(-1);
    }
    strncpy(directory + len, FindFileData.cFileName, 499 - len);
    ret->gl_pathv[ret->gl_pathc] = strdup(directory);
    if (ret->gl_pathv[ret->gl_pathc] == NULL)
        goto done;
    ret->gl_pathc++;
    while(FindNextFileA(hFind, &FindFileData)) {
        if (FindFileData.cFileName[0] == '.')
	    continue;
        if (ret->gl_pathc + 2 > nb_paths) {
            char **tmp = realloc(ret->gl_pathv, nb_paths * 2 * sizeof(char *));
            if (tmp == NULL)
                break;
            ret->gl_pathv = tmp;
            nb_paths *= 2;
	}
	strncpy(directory + len, FindFileData.cFileName, 499 - len);
	ret->gl_pathv[ret->gl_pathc] = strdup(directory);
        if (ret->gl_pathv[ret->gl_pathc] == NULL)
            break;
        ret->gl_pathc++;
    }
    ret->gl_pathv[ret->gl_pathc] = NULL;

done:
    FindClose(hFind);
    return(0);
}
