set_buffer_environ(Buffer *buf)
{
    static Buffer *prev_buf = NULL;
    static Line *prev_line = NULL;
    static int prev_pos = -1;
    Line *l;

    if (buf == NULL)
	return;
    if (buf != prev_buf) {
	set_environ("W3M_SOURCEFILE", buf->sourcefile);
	set_environ("W3M_FILENAME", buf->filename);
	set_environ("W3M_TITLE", buf->buffername);
	set_environ("W3M_URL", parsedURL2Str(&buf->currentURL)->ptr);
	set_environ("W3M_TYPE", buf->real_type ? buf->real_type : "unknown");
#ifdef USE_M17N
	set_environ("W3M_CHARSET", wc_ces_to_charset(buf->document_charset));
#endif
    }
    l = buf->currentLine;
    if (l && (buf != prev_buf || l != prev_line || buf->pos != prev_pos)) {
	Anchor *a;
	ParsedURL pu;
	char *s = GetWord(buf);
	set_environ("W3M_CURRENT_WORD", s ? s : "");
	a = retrieveCurrentAnchor(buf);
	if (a) {
	    parseURL2(a->url, &pu, baseURL(buf));
	    set_environ("W3M_CURRENT_LINK", parsedURL2Str(&pu)->ptr);
	}
	else
	    set_environ("W3M_CURRENT_LINK", "");
	a = retrieveCurrentImg(buf);
	if (a) {
	    parseURL2(a->url, &pu, baseURL(buf));
	    set_environ("W3M_CURRENT_IMG", parsedURL2Str(&pu)->ptr);
	}
	else
	    set_environ("W3M_CURRENT_IMG", "");
	a = retrieveCurrentForm(buf);
	if (a)
	    set_environ("W3M_CURRENT_FORM", form2str((FormItemList *)a->url));
	else
	    set_environ("W3M_CURRENT_FORM", "");
	set_environ("W3M_CURRENT_LINE", Sprintf("%ld",
						l->real_linenumber)->ptr);
	set_environ("W3M_CURRENT_COLUMN", Sprintf("%d",
						  buf->currentColumn +
						  buf->cursorX + 1)->ptr);
    }
    else if (!l) {
	set_environ("W3M_CURRENT_WORD", "");
	set_environ("W3M_CURRENT_LINK", "");
	set_environ("W3M_CURRENT_IMG", "");
	set_environ("W3M_CURRENT_FORM", "");
	set_environ("W3M_CURRENT_LINE", "0");
	set_environ("W3M_CURRENT_COLUMN", "0");
    }
    prev_buf = buf;
    prev_line = l;
    prev_pos = buf->pos;
}
