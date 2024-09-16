streamParseTest(const char *filename, const char *result, const char *err,
                int options) {
    xmlTextReaderPtr reader;
    int ret;

    reader = xmlReaderForFile(filename, NULL, options);
    ret = streamProcessTest(filename, result, err, reader, NULL, options);
    xmlFreeTextReader(reader);
    return(ret);
}
