inputPush(xmlParserCtxtPtr ctxt, xmlParserInputPtr value)
{
    if ((ctxt == NULL) || (value == NULL))
        return(-1);
    if (ctxt->inputNr >= ctxt->inputMax) {
        ctxt->inputMax *= 2;
        ctxt->inputTab =
            (xmlParserInputPtr *) xmlRealloc(ctxt->inputTab,
                                             ctxt->inputMax *
                                             sizeof(ctxt->inputTab[0]));
        if (ctxt->inputTab == NULL) {
            xmlErrMemory(ctxt, NULL);
	    xmlFreeInputStream(value);
	    ctxt->inputMax /= 2;
	    value = NULL;
            return (-1);
        }
    }
    ctxt->inputTab[ctxt->inputNr] = value;
    ctxt->input = value;
    return (ctxt->inputNr++);
}
