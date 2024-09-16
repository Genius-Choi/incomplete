save_buffer_position(Buffer *buf)
{
    BufferPos *b = buf->undo;

    if (!buf->firstLine)
	return;
    if (b && b->top_linenumber == TOP_LINENUMBER(buf) &&
	b->cur_linenumber == CUR_LINENUMBER(buf) &&
	b->currentColumn == buf->currentColumn && b->pos == buf->pos)
	return;
    b = New(BufferPos);
    b->top_linenumber = TOP_LINENUMBER(buf);
    b->cur_linenumber = CUR_LINENUMBER(buf);
    b->currentColumn = buf->currentColumn;
    b->pos = buf->pos;
    b->bpos = buf->currentLine ? buf->currentLine->bpos : 0;
    b->next = NULL;
    b->prev = buf->undo;
    if (buf->undo)
	buf->undo->next = b;
    buf->undo = b;
}
