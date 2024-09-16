xml2_read_cb(void *context, char *buffer, int len)
{
	struct archive_read *a;
	struct xar *xar;
	const void *d;
	size_t outbytes;
	size_t used = 0;
	int r;

	a = (struct archive_read *)context;
	xar = (struct xar *)(a->format->data);

	if (xar->toc_remaining <= 0)
		return (0);
	d = buffer;
	outbytes = len;
	r = rd_contents(a, &d, &outbytes, &used, xar->toc_remaining);
	if (r != ARCHIVE_OK)
		return (r);
	__archive_read_consume(a, used);
	xar->toc_remaining -= used;
	xar->offset += used;
	xar->toc_total += outbytes;
	PRINT_TOC(buffer, len);

	return ((int)outbytes);
}
