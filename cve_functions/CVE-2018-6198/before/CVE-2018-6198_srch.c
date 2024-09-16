srch(int (*func) (Buffer *, char *), char *prompt)
{
    char *str;
    int result;
    int disp = FALSE;
    int pos;

    str = searchKeyData();
    if (str == NULL || *str == '\0') {
	str = inputStrHist(prompt, NULL, TextHist);
	if (str != NULL && *str == '\0')
	    str = SearchString;
	if (str == NULL) {
	    displayBuffer(Currentbuf, B_NORMAL);
	    return;
	}
	disp = TRUE;
    }
    pos = Currentbuf->pos;
    if (func == forwardSearch)
	Currentbuf->pos += 1;
    result = srchcore(str, func);
    if (result & SR_FOUND)
	clear_mark(Currentbuf->currentLine);
    else
	Currentbuf->pos = pos;
    displayBuffer(Currentbuf, B_NORMAL);
    if (disp)
	disp_srchresult(result, prompt, str);
    searchRoutine = func;
}
