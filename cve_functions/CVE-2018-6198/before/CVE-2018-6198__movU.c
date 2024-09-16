_movU(int n)
{
    int i, m = searchKeyNum();
    if (Currentbuf->firstLine == NULL)
	return;
    for (i = 0; i < m; i++)
	cursorUp(Currentbuf, n);
    displayBuffer(Currentbuf, B_NORMAL);
}
