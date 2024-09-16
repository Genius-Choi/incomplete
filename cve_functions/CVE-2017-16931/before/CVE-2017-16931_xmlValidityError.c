xmlValidityError(xmlParserCtxtPtr ctxt, xmlParserErrors error,
              const char *msg, const xmlChar *str1, const xmlChar *str2)
{
    xmlStructuredErrorFunc schannel = NULL;

    if ((ctxt != NULL) && (ctxt->disableSAX != 0) &&
        (ctxt->instate == XML_PARSER_EOF))
	return;
    if (ctxt != NULL) {
	ctxt->errNo = error;
	if ((ctxt->sax != NULL) && (ctxt->sax->initialized == XML_SAX2_MAGIC))
	    schannel = ctxt->sax->serror;
    }
    if (ctxt != NULL) {
        __xmlRaiseError(schannel,
                    ctxt->vctxt.error, ctxt->vctxt.userData,
                    ctxt, NULL, XML_FROM_DTD, error,
                    XML_ERR_ERROR, NULL, 0, (const char *) str1,
		    (const char *) str2, NULL, 0, 0,
		    msg, (const char *) str1, (const char *) str2);
	ctxt->valid = 0;
    } else {
        __xmlRaiseError(schannel, NULL, NULL,
                    ctxt, NULL, XML_FROM_DTD, error,
                    XML_ERR_ERROR, NULL, 0, (const char *) str1,
		    (const char *) str2, NULL, 0, 0,
		    msg, (const char *) str1, (const char *) str2);
    }
}
