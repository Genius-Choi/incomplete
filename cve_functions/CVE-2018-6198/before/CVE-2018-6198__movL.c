_movL(int n)
{
    int i, m = searchKeyNum();
    if (Currentbuf->firstLine == NULL)
	return;
    for (i = 0; i < m; i++)
	cursorLeft(Currentbuf, n);
    displayBuffer(Currentbuf, B_NORMAL);
}
