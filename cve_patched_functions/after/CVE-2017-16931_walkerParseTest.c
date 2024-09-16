walkerParseTest(const char *filename, const char *result, const char *err,
                int options) {
    xmlDocPtr doc;
    xmlTextReaderPtr reader;
    int ret;

    doc = xmlReadFile(filename, NULL, options);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse %s\n", filename);
	return(-1);
    }
    reader = xmlReaderWalker(doc);
    ret = streamProcessTest(filename, result, err, reader, NULL, options);
    xmlFreeTextReader(reader);
    xmlFreeDoc(doc);
    return(ret);
}
