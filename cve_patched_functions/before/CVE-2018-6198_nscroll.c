nscroll(int n, int mode)
{
    Buffer *buf = Currentbuf;
    Line *top = buf->topLine, *cur = buf->currentLine;
    int lnum, tlnum, llnum, diff_n;

    if (buf->firstLine == NULL)
	return;
    lnum = cur->linenumber;
    buf->topLine = lineSkip(buf, top, n, FALSE);
    if (buf->topLine == top) {
	lnum += n;
	if (lnum < buf->topLine->linenumber)
	    lnum = buf->topLine->linenumber;
	else if (lnum > buf->lastLine->linenumber)
	    lnum = buf->lastLine->linenumber;
    }
    else {
	tlnum = buf->topLine->linenumber;
	llnum = buf->topLine->linenumber + buf->LINES - 1;
	if (nextpage_topline)
	    diff_n = 0;
	else
	    diff_n = n - (tlnum - top->linenumber);
	if (lnum < tlnum)
	    lnum = tlnum + diff_n;
	if (lnum > llnum)
	    lnum = llnum + diff_n;
    }
    gotoLine(buf, lnum);
    arrangeLine(buf);
    if (n > 0) {
	if (buf->currentLine->bpos &&
	    buf->currentLine->bwidth >= buf->currentColumn + buf->visualpos)
	    cursorDown(buf, 1);
	else {
	    while (buf->currentLine->next && buf->currentLine->next->bpos &&
		   buf->currentLine->bwidth + buf->currentLine->width <
		   buf->currentColumn + buf->visualpos)
		cursorDown0(buf, 1);
	}
    }
    else {
	if (buf->currentLine->bwidth + buf->currentLine->width <
	    buf->currentColumn + buf->visualpos)
	    cursorUp(buf, 1);
	else {
	    while (buf->currentLine->prev && buf->currentLine->bpos &&
		   buf->currentLine->bwidth >=
		   buf->currentColumn + buf->visualpos)
		cursorUp0(buf, 1);
	}
    }
    displayBuffer(buf, mode);
}
