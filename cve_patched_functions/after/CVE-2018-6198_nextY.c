nextY(int d)
{
    HmarkerList *hl = Currentbuf->hmarklist;
    Anchor *an, *pan;
    int i, x, y, n = searchKeyNum();
    int hseq;

    if (Currentbuf->firstLine == NULL)
	return;
    if (!hl || hl->nmark == 0)
	return;

    an = retrieveCurrentAnchor(Currentbuf);
    if (an == NULL)
	an = retrieveCurrentForm(Currentbuf);

    x = Currentbuf->pos;
    y = Currentbuf->currentLine->linenumber + d;
    pan = NULL;
    hseq = -1;
    for (i = 0; i < n; i++) {
	if (an)
	    hseq = abs(an->hseq);
	an = NULL;
	for (; y >= 0 && y <= Currentbuf->lastLine->linenumber; y += d) {
	    an = retrieveAnchor(Currentbuf->href, y, x);
	    if (!an)
		an = retrieveAnchor(Currentbuf->formitem, y, x);
	    if (an && hseq != abs(an->hseq)) {
		pan = an;
		break;
	    }
	}
	if (!an)
	    break;
    }

    if (pan == NULL)
	return;
    gotoLine(Currentbuf, pan->start.line);
    arrangeLine(Currentbuf);
    displayBuffer(Currentbuf, B_NORMAL);
}
