GetWord(Buffer *buf)
{
    int b, e;
    char *p;

    if ((p = getCurWord(buf, &b, &e)) != NULL) {
	return Strnew_charp_n(p, e - b)->ptr;
    }
    return NULL;
}
