handleURI(const char *str, const char *base, FILE *o) {
    int ret;
    xmlURIPtr uri;
    xmlChar *res = NULL;

    uri = xmlCreateURI();

    if (base == NULL) {
	ret = xmlParseURIReference(uri, str);
	if (ret != 0)
	    fprintf(o, "%s : error %d\n", str, ret);
	else {
	    xmlNormalizeURIPath(uri->path);
	    xmlPrintURI(o, uri);
	    fprintf(o, "\n");
	}
    } else {
	res = xmlBuildURI((xmlChar *)str, (xmlChar *) base);
	if (res != NULL) {
	    fprintf(o, "%s\n", (char *) res);
	}
	else
	    fprintf(o, "::ERROR::\n");
    }
    if (res != NULL)
	xmlFree(res);
    xmlFreeURI(uri);
}
