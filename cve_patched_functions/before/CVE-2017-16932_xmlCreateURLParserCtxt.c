xmlCreateURLParserCtxt(const char *filename, int options)
{
    xmlParserCtxtPtr ctxt;
    xmlParserInputPtr inputStream;
    char *directory = NULL;

    ctxt = xmlNewParserCtxt();
    if (ctxt == NULL) {
	xmlErrMemory(NULL, "cannot allocate parser context");
	return(NULL);
    }

    if (options)
	xmlCtxtUseOptionsInternal(ctxt, options, NULL);
    ctxt->linenumbers = 1;

    inputStream = xmlLoadExternalEntity(filename, NULL, ctxt);
    if (inputStream == NULL) {
	xmlFreeParserCtxt(ctxt);
	return(NULL);
    }

    inputPush(ctxt, inputStream);
    if ((ctxt->directory == NULL) && (directory == NULL))
        directory = xmlParserGetDirectory(filename);
    if ((ctxt->directory == NULL) && (directory != NULL))
        ctxt->directory = directory;

    return(ctxt);
}
