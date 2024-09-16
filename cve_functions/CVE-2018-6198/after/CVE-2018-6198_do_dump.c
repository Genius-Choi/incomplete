do_dump(Buffer *buf)
{
    MySignalHandler(*volatile prevtrap) (SIGNAL_ARG) = NULL;

    prevtrap = mySignal(SIGINT, intTrap);
    if (SETJMP(IntReturn) != 0) {
	mySignal(SIGINT, prevtrap);
	return;
    }
    if (w3m_dump & DUMP_EXTRA)
	dump_extra(buf);
    if (w3m_dump & DUMP_HEAD)
	dump_head(buf);
    if (w3m_dump & DUMP_SOURCE)
	dump_source(buf);
    if (w3m_dump == DUMP_BUFFER) {
	int i;
	saveBuffer(buf, stdout, FALSE);
	if (displayLinkNumber && buf->href) {
	    int nanchor = buf->href->nanchor;
	    printf("\nReferences:\n\n");
	    Anchor **in_order = New_N(Anchor *, buf->href->nanchor);
	    for (i = 0; i < nanchor; i++)
		in_order[i] = buf->href->anchors + i;
	    qsort(in_order, nanchor, sizeof(Anchor *), cmp_anchor_hseq);
	    for (i = 0; i < nanchor; i++) {
		ParsedURL pu;
		char *url;
		if (in_order[i]->slave)
		    continue;
		parseURL2(in_order[i]->url, &pu, baseURL(buf));
		url = url_decode2(parsedURL2Str(&pu)->ptr, Currentbuf);
		printf("[%d] %s\n", in_order[i]->hseq + 1, url);
	    }
	}
    }
    mySignal(SIGINT, prevtrap);
}
