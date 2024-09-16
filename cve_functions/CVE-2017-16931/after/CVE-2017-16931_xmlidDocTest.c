xmlidDocTest(const char *filename,
             const char *result,
             const char *err,
             int options) {

    int res = 0;
    int ret = 0;
    char *temp;

    xpathDocument = xmlReadFile(filename, NULL,
                                options | XML_PARSE_DTDATTR | XML_PARSE_NOENT);
    if (xpathDocument == NULL) {
        fprintf(stderr, "Failed to load %s\n", filename);
	return(-1);
    }

    temp = resultFilename(filename, "", ".res");
    if (temp == NULL) {
        fprintf(stderr, "Out of memory\n");
        fatalError();
    }
    xpathOutput = fopen(temp, "wb");
    if (xpathOutput == NULL) {
	fprintf(stderr, "failed to open output file %s\n", temp);
        xmlFreeDoc(xpathDocument);
        free(temp);
	return(-1);
    }

    testXPath("id('bar')", 0, 0);

    fclose(xpathOutput);
    if (result != NULL) {
	ret = compareFiles(temp, result);
	if (ret) {
	    fprintf(stderr, "Result for %s failed in %s\n", filename, result);
	    res = 1;
	}
    }

    if (temp != NULL) {
        unlink(temp);
        free(temp);
    }
    xmlFreeDoc(xpathDocument);

    if (err != NULL) {
	ret = compareFileMem(err, testErrors, testErrorsSize);
	if (ret != 0) {
	    fprintf(stderr, "Error for %s failed\n", filename);
	    res = 1;
	}
    }
    return(res);
}
