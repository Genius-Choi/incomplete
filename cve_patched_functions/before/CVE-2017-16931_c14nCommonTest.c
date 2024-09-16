c14nCommonTest(const char *filename, int with_comments, int mode,
               const char *subdir) {
    char buf[500];
    char prefix[500];
    const char *base;
    int len;
    char *result = NULL;
    char *xpath = NULL;
    char *ns = NULL;
    int ret = 0;

    base = baseFilename(filename);
    len = strlen(base);
    len -= 4;
    memcpy(prefix, base, len);
    prefix[len] = 0;

    snprintf(buf, 499, "result/c14n/%s/%s", subdir,prefix);
    if (!checkTestFile(buf) && !update_results) {
        fprintf(stderr, "Missing result file %s", buf);
	return(-1);
    }
    result = strdup(buf);
    snprintf(buf, 499, "test/c14n/%s/%s.xpath", subdir,prefix);
    if (checkTestFile(buf)) {
	xpath = strdup(buf);
    }
    snprintf(buf, 499, "test/c14n/%s/%s.ns", subdir,prefix);
    if (checkTestFile(buf)) {
	ns = strdup(buf);
    }

    nb_tests++;
    if (c14nRunTest(filename, with_comments, mode,
                    xpath, ns, result) < 0)
        ret = 1;

    if (result != NULL) free(result);
    if (xpath != NULL) free(xpath);
    if (ns != NULL) free(ns);
    return(ret);
}
