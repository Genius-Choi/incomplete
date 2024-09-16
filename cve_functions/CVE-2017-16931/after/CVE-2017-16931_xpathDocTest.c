xpathDocTest(const char *filename,
             const char *resul ATTRIBUTE_UNUSED,
             const char *err ATTRIBUTE_UNUSED,
             int options) {

    char pattern[500];
    char result[500];
    glob_t globbuf;
    size_t i;
    int ret = 0, res;

    xpathDocument = xmlReadFile(filename, NULL,
                                options | XML_PARSE_DTDATTR | XML_PARSE_NOENT);
    if (xpathDocument == NULL) {
        fprintf(stderr, "Failed to load %s\n", filename);
	return(-1);
    }

    snprintf(pattern, 499, "./test/XPath/tests/%s*", baseFilename(filename));
    pattern[499] = 0;
    globbuf.gl_offs = 0;
    glob(pattern, GLOB_DOOFFS, NULL, &globbuf);
    for (i = 0;i < globbuf.gl_pathc;i++) {
        snprintf(result, 499, "result/XPath/tests/%s",
	         baseFilename(globbuf.gl_pathv[i]));
	res = xpathCommonTest(globbuf.gl_pathv[i], &result[0], 0, 0);
	if (res != 0)
	    ret = res;
    }
    globfree(&globbuf);

    xmlFreeDoc(xpathDocument);
    return(ret);
}
