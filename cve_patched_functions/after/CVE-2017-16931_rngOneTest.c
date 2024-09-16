rngOneTest(const char *sch,
               const char *filename,
               const char *result,
	       const char *err,
	       int options,
	       xmlRelaxNGPtr schemas) {
    xmlDocPtr doc;
    xmlRelaxNGValidCtxtPtr ctxt;
    int ret = 0;
    char *temp;
    FILE *schemasOutput;

    doc = xmlReadFile(filename, NULL, options);
    if (doc == NULL) {
        fprintf(stderr, "failed to parse instance %s for %s\n", filename, sch);
	return(-1);
    }

    temp = resultFilename(result, "", ".res");
    if (temp == NULL) {
        fprintf(stderr, "Out of memory\n");
        fatalError();
    }
    schemasOutput = fopen(temp, "wb");
    if (schemasOutput == NULL) {
	fprintf(stderr, "failed to open output file %s\n", temp);
	xmlFreeDoc(doc);
        free(temp);
	return(-1);
    }

    ctxt = xmlRelaxNGNewValidCtxt(schemas);
    xmlRelaxNGSetValidErrors(ctxt,
         (xmlRelaxNGValidityErrorFunc) testErrorHandler,
         (xmlRelaxNGValidityWarningFunc) testErrorHandler,
	 ctxt);
    ret = xmlRelaxNGValidateDoc(ctxt, doc);
    if (ret == 0) {
	testErrorHandler(NULL, "%s validates\n", filename);
    } else if (ret > 0) {
	testErrorHandler(NULL, "%s fails to validate\n", filename);
    } else {
	testErrorHandler(NULL, "%s validation generated an internal error\n",
	       filename);
    }
    fclose(schemasOutput);
    ret = 0;
    if (result) {
	if (compareFiles(temp, result)) {
	    fprintf(stderr, "Result for %s on %s failed\n", filename, sch);
	    ret = 1;
	}
    }
    if (temp != NULL) {
        unlink(temp);
        free(temp);
    }

    if (err != NULL) {
	if (compareFileMem(err, testErrors, testErrorsSize)) {
	    fprintf(stderr, "Error for %s on %s failed\n", filename, sch);
	    ret = 1;
	    printf("%s", testErrors);
	}
    }


    xmlRelaxNGFreeValidCtxt(ctxt);
    xmlFreeDoc(doc);
    return(ret);
}
