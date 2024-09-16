dump_source(Buffer *buf)
{
    FILE *f;
    int c;
    if (buf->sourcefile == NULL)
	return;
    f = fopen(buf->sourcefile, "r");
    if (f == NULL)
	return;
    while ((c = fgetc(f)) != EOF) {
	putchar(c);
    }
    fclose(f);
}
