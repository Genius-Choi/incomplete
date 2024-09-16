xmlDoRead(xmlParserCtxtPtr ctxt, const char *URL, const char *encoding,
          int options, int reuse)
{
    xmlDocPtr ret;

    xmlCtxtUseOptionsInternal(ctxt, options, encoding);
    if (encoding != NULL) {
        xmlCharEncodingHandlerPtr hdlr;

	hdlr = xmlFindCharEncodingHandler(encoding);
	if (hdlr != NULL)
	    xmlSwitchToEncoding(ctxt, hdlr);
    }
    if ((URL != NULL) && (ctxt->input != NULL) &&
        (ctxt->input->filename == NULL))
        ctxt->input->filename = (char *) xmlStrdup((const xmlChar *) URL);
    xmlParseDocument(ctxt);
    if ((ctxt->wellFormed) || ctxt->recovery)
        ret = ctxt->myDoc;
    else {
        ret = NULL;
	if (ctxt->myDoc != NULL) {
	    xmlFreeDoc(ctxt->myDoc);
	}
    }
    ctxt->myDoc = NULL;
    if (!reuse) {
	xmlFreeParserCtxt(ctxt);
    }

    return (ret);
}
