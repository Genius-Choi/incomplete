clear_mark(Line *l)
{
    int pos;
    if (!l)
	return;
    for (pos = 0; pos < l->size; pos++)
	l->propBuf[pos] &= ~PE_MARK;
}
