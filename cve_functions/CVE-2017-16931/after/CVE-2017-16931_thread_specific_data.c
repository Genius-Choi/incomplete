thread_specific_data(void *private_data)
{
    xmlDocPtr myDoc;
    const char *filename = (const char *) private_data;
    int okay = 1;

    if (!strcmp(filename, "test/threads/invalid.xml")) {
        xmlDoValidityCheckingDefaultValue = 0;
        xmlGenericErrorContext = stdout;
    } else {
        xmlDoValidityCheckingDefaultValue = 1;
        xmlGenericErrorContext = stderr;
    }
    myDoc = xmlParseFile(filename);
    if (myDoc) {
        xmlFreeDoc(myDoc);
    } else {
        printf("parse failed\n");
        okay = 0;
    }
    if (!strcmp(filename, "test/threads/invalid.xml")) {
        if (xmlDoValidityCheckingDefaultValue != 0) {
            printf("ValidityCheckingDefaultValue override failed\n");
            okay = 0;
        }
        if (xmlGenericErrorContext != stdout) {
            printf("xmlGenericErrorContext override failed\n");
            okay = 0;
        }
    } else {
        if (xmlDoValidityCheckingDefaultValue != 1) {
            printf("ValidityCheckingDefaultValue override failed\n");
            okay = 0;
        }
        if (xmlGenericErrorContext != stderr) {
            printf("xmlGenericErrorContext override failed\n");
            okay = 0;
        }
    }
    if (okay == 0)
        return ((void *) Failed);
    return ((void *) Okay);
}
