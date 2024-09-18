static void xdr_set_next_page(struct xdr_stream *xdr)
{
	unsigned int newbase;

	newbase = (1 + xdr->page_ptr - xdr->buf->pages) << PAGE_SHIFT;
	newbase -= xdr->buf->page_base;

	if (xdr_set_page_base(xdr, newbase, PAGE_SIZE) < 0)
		xdr_set_iov(xdr, xdr->buf->tail, NULL, xdr->buf->len);
}
