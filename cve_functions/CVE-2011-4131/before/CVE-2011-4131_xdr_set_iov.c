static void xdr_set_iov(struct xdr_stream *xdr, struct kvec *iov,
		__be32 *p, unsigned int len)
{
	if (len > iov->iov_len)
		len = iov->iov_len;
	if (p == NULL)
		p = (__be32*)iov->iov_base;
	xdr->p = p;
	xdr->end = (__be32*)(iov->iov_base + len);
	xdr->iov = iov;
	xdr->page_ptr = NULL;
}
