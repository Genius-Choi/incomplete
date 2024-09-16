nextX(int d, int dy)
{
    HmarkerList *hl = Currentbuf->hmarklist;
    Anchor *an, *pan;
    Line *l;
    int i, x, y, n = searchKeyNum();

    if (Currentbuf->firstLine == NULL)
	return;
    if (!hl || hl->nmark == 0)
	return;

    an = retrieveCurrentAnchor(Currentbuf);
    if (an == NULL)
	an = retrieveCurrentForm(Currentbuf);

    l = Currentbuf->currentLine;
    x = Currentbuf->pos;
    y = l->linenumber;
    pan = NULL;
    for (i = 0; i < n; i++) {
	if (an)
	    x = (d > 0) ? an->end.pos : an->start.pos - 1;
	an = NULL;
	while (1) {
	    for (; x >= 0 && x < l->len; x += d) {
		an = retrieveAnchor(Currentbuf->href, y, x);
		if (!an)
		    an = retrieveAnchor(Currentbuf->formitem, y, x);
		if (an) {
		    pan = an;
		    break;
		}
	    }
	    if (!dy || an)
		break;
	    l = (dy > 0) ? l->next : l->prev;
	    if (!l)
		break;
	    x = (d > 0) ? 0 : l->len - 1;
	    y = l->linenumber;
	}
	if (!an)
	    break;
    }

    if (pan == NULL)
	return;
    gotoLine(Currentbuf, y);
    Currentbuf->pos = pan->start.pos;
    arrangeCursor(Currentbuf);
    displayBuffer(Currentbuf, B_NORMAL);
}
