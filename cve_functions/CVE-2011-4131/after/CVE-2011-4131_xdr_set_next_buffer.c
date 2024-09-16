static bool xdr_set_next_buffer(struct xdr_stream *xdr)
{
	if (xdr->page_ptr != NULL)
		xdr_set_next_page(xdr);
	else if (xdr->iov == xdr->buf->head) {
		if (xdr_set_page_base(xdr, 0, PAGE_SIZE) < 0)
			xdr_set_iov(xdr, xdr->buf->tail, NULL, xdr->buf->len);
	}
	return xdr->p != xdr->end;
}
