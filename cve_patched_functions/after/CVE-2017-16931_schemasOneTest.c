schemasOneTest(const char *sch,
               const char *filename,
               const char *result,
	       const char *err,
	       int options,
	       xmlSchemaPtr schemas) {
    xmlDocPtr doc;
    xmlSchemaValidCtxtPtr ctxt;
    int ret = 0;
    int validResult = 0;
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

    ctxt = xmlSchemaNewValidCtxt(schemas);
    xmlSchemaSetValidErrors(ctxt,
         (xmlSchemaValidityErrorFunc) testErrorHandler,
         (xmlSchemaValidityWarningFunc) testErrorHandler,
	 ctxt);
    validResult = xmlSchemaValidateDoc(ctxt, doc);
    if (validResult == 0) {
	fprintf(schemasOutput, "%s validates\n", filename);
    } else if (validResult > 0) {
	fprintf(schemasOutput, "%s fails to validate\n", filename);
    } else {
	fprintf(schemasOutput, "%s validation generated an internal error\n",
	       filename);
    }
    fclose(schemasOutput);
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

    if ((validResult != 0) && (err != NULL)) {
	if (compareFileMem(err, testErrors, testErrorsSize)) {
	    fprintf(stderr, "Error for %s on %s failed\n", filename, sch);
	    ret = 1;
	}
    }

    xmlSchemaFreeValidCtxt(ctxt);
    xmlFreeDoc(doc);
    return(ret);
}
