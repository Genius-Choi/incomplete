static int spacePush(xmlParserCtxtPtr ctxt, int val) {
    if (ctxt->spaceNr >= ctxt->spaceMax) {
        int *tmp;

	ctxt->spaceMax *= 2;
        tmp = (int *) xmlRealloc(ctxt->spaceTab,
	                         ctxt->spaceMax * sizeof(ctxt->spaceTab[0]));
        if (tmp == NULL) {
	    xmlErrMemory(ctxt, NULL);
	    ctxt->spaceMax /=2;
	    return(-1);
	}
	ctxt->spaceTab = tmp;
    }
    ctxt->spaceTab[ctxt->spaceNr] = val;
    ctxt->space = &ctxt->spaceTab[ctxt->spaceNr];
    return(ctxt->spaceNr++);
}
