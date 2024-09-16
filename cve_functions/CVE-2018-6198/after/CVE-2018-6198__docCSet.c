_docCSet(wc_ces charset)
{
    if (Currentbuf->bufferprop & BP_INTERNAL)
	return;
    if (Currentbuf->sourcefile == NULL) {
	disp_message("Can't reload...", FALSE);
	return;
    }
    Currentbuf->document_charset = charset;
    Currentbuf->need_reshape = TRUE;
    displayBuffer(Currentbuf, B_FORCE_REDRAW);
}
