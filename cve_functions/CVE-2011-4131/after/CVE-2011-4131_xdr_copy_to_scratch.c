static __be32 *xdr_copy_to_scratch(struct xdr_stream *xdr, size_t nbytes)
{
	__be32 *p;
	void *cpdest = xdr->scratch.iov_base;
	size_t cplen = (char *)xdr->end - (char *)xdr->p;

	if (nbytes > xdr->scratch.iov_len)
		return NULL;
	memcpy(cpdest, xdr->p, cplen);
	cpdest += cplen;
	nbytes -= cplen;
	if (!xdr_set_next_buffer(xdr))
		return NULL;
	p = __xdr_inline_decode(xdr, nbytes);
	if (p == NULL)
		return NULL;
	memcpy(cpdest, p, nbytes);
	return xdr->scratch.iov_base;
}
