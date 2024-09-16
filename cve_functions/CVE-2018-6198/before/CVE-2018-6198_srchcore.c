srchcore(char *volatile str, int (*func) (Buffer *, char *))
{
    MySignalHandler(*prevtrap) ();
    volatile int i, result = SR_NOTFOUND;

    if (str != NULL && str != SearchString)
	SearchString = str;
    if (SearchString == NULL || *SearchString == '\0')
	return SR_NOTFOUND;

    str = conv_search_string(SearchString, DisplayCharset);
    prevtrap = mySignal(SIGINT, intTrap);
    crmode();
    if (SETJMP(IntReturn) == 0) {
	for (i = 0; i < PREC_NUM; i++) {
	    result = func(Currentbuf, str);
	    if (i < PREC_NUM - 1 && result & SR_FOUND)
		clear_mark(Currentbuf->currentLine);
	}
    }
    mySignal(SIGINT, prevtrap);
    term_raw();
    return result;
}
