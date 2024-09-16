prev_nonnull_line(Line *line)
{
    Line *l;

    for (l = line; l != NULL && l->len == 0; l = l->prev) ;
    if (l == NULL || l->len == 0)
	return -1;

    Currentbuf->currentLine = l;
    if (l != line)
	Currentbuf->pos = Currentbuf->currentLine->len;
    return 0;
}
