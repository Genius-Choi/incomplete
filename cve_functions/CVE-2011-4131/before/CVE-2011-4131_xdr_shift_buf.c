xdr_shift_buf(struct xdr_buf *buf, size_t len)
{
	xdr_shrink_bufhead(buf, len);
}
