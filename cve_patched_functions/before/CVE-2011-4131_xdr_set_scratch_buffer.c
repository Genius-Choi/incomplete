void xdr_set_scratch_buffer(struct xdr_stream *xdr, void *buf, size_t buflen)
{
	xdr->scratch.iov_base = buf;
	xdr->scratch.iov_len = buflen;
}
