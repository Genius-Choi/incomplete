void xdr_init_decode(struct xdr_stream *xdr, struct xdr_buf *buf, __be32 *p)
{
	xdr->buf = buf;
	xdr->scratch.iov_base = NULL;
	xdr->scratch.iov_len = 0;
	if (buf->head[0].iov_len != 0)
		xdr_set_iov(xdr, buf->head, p, buf->len);
	else if (buf->page_len != 0)
		xdr_set_page_base(xdr, 0, buf->len);
}
