errParseTest(const char *filename, const char *result, const char *err,
             int options) {
    xmlDocPtr doc;
    const char *base = NULL;
    int size, res = 0;

    nb_tests++;
#ifdef LIBXML_HTML_ENABLED
    if (options & XML_PARSE_HTML) {
        doc = htmlReadFile(filename, NULL, options);
    } else
#endif
#ifdef LIBXML_XINCLUDE_ENABLED
    if (options & XML_PARSE_XINCLUDE) {
	doc = xmlReadFile(filename, NULL, options);
	xmlXIncludeProcessFlags(doc, options);
    } else
#endif
    {
	xmlGetWarningsDefaultValue = 1;
	doc = xmlReadFile(filename, NULL, options);
    }
    xmlGetWarningsDefaultValue = 0;
    if (result) {
	if (doc == NULL) {
	    base = "";
	    size = 0;
	} else {
#ifdef LIBXML_HTML_ENABLED
	    if (options & XML_PARSE_HTML) {
		htmlDocDumpMemory(doc, (xmlChar **) &base, &size);
	    } else
#endif
	    xmlDocDumpMemory(doc, (xmlChar **) &base, &size);
	}
	res = compareFileMem(result, base, size);
	if (res != 0) {
	    fprintf(stderr, "Result for %s failed in %s\n", filename, result);
	    return(-1);
	}
    }
    if (doc != NULL) {
	if (base != NULL)
	    xmlFree((char *)base);
	xmlFreeDoc(doc);
    }
    if (err != NULL) {
	res = compareFileMem(err, testErrors, testErrorsSize);
	if (res != 0) {
	    fprintf(stderr, "Error for %s failed\n", filename);
	    return(-1);
	}
    } else if (options & XML_PARSE_DTDVALID) {
        if (testErrorsSize != 0)
	    fprintf(stderr, "Validation for %s failed\n", filename);
    }

    return(0);
}
