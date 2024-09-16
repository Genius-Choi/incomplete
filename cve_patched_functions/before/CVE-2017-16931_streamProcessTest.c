streamProcessTest(const char *filename, const char *result, const char *err,
                  xmlTextReaderPtr reader, const char *rng, int options) {
    int ret;
    char *temp = NULL;
    FILE *t = NULL;

    if (reader == NULL)
        return(-1);

    nb_tests++;
    if (result != NULL) {
	temp = resultFilename(filename, "", ".res");
	if (temp == NULL) {
	    fprintf(stderr, "Out of memory\n");
	    fatalError();
	}
	t = fopen(temp, "wb");
	if (t == NULL) {
	    fprintf(stderr, "Can't open temp file %s\n", temp);
	    free(temp);
	    return(-1);
	}
    }
#ifdef LIBXML_SCHEMAS_ENABLED
    if (rng != NULL) {
	ret = xmlTextReaderRelaxNGValidate(reader, rng);
	if (ret < 0) {
	    testErrorHandler(NULL, "Relax-NG schema %s failed to compile\n",
	                     rng);
	    fclose(t);
            if (temp != NULL) {
                unlink(temp);
                free(temp);
            }
	    return(0);
	}
    }
#endif
    xmlGetWarningsDefaultValue = 1;
    ret = xmlTextReaderRead(reader);
    while (ret == 1) {
	if ((t != NULL) && (rng == NULL))
	    processNode(t, reader);
        ret = xmlTextReaderRead(reader);
    }
    if (ret != 0) {
        testErrorHandler(NULL, "%s : failed to parse\n", filename);
    }
    if (rng != NULL) {
        if (xmlTextReaderIsValid(reader) != 1) {
	    testErrorHandler(NULL, "%s fails to validate\n", filename);
	} else {
	    testErrorHandler(NULL, "%s validates\n", filename);
	}
    }
    xmlGetWarningsDefaultValue = 0;
    if (t != NULL) {
        fclose(t);
	ret = compareFiles(temp, result);
        if (temp != NULL) {
            unlink(temp);
            free(temp);
        }
	if (ret) {
	    fprintf(stderr, "Result for %s failed in %s\n", filename, result);
	    return(-1);
	}
    }
    if (err != NULL) {
	ret = compareFileMem(err, testErrors, testErrorsSize);
	if (ret != 0) {
	    fprintf(stderr, "Error for %s failed\n", filename);
	    printf("%s", testErrors);
	    return(-1);
	}
    }

    return(0);
}
