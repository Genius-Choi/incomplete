_newT(void)
{
    TabBuffer *tag;
    Buffer *buf;
    int i;

    tag = newTab();
    if (!tag)
	return;

    buf = newBuffer(Currentbuf->width);
    copyBuffer(buf, Currentbuf);
    buf->nextBuffer = NULL;
    for (i = 0; i < MAX_LB; i++)
	buf->linkBuffer[i] = NULL;
    (*buf->clone)++;
    tag->firstBuffer = tag->currentBuffer = buf;

    tag->nextTab = CurrentTab->nextTab;
    tag->prevTab = CurrentTab;
    if (CurrentTab->nextTab)
	CurrentTab->nextTab->prevTab = tag;
    else
	LastTab = tag;
    CurrentTab->nextTab = tag;
    CurrentTab = tag;
    nTab++;
}
