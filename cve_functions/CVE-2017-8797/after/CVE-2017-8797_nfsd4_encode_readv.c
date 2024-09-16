static __be32 nfsd4_encode_readv(struct nfsd4_compoundres *resp,
				 struct nfsd4_read *read,
				 struct file *file, unsigned long maxcount)
{
	struct xdr_stream *xdr = &resp->xdr;
	u32 eof;
	int v;
	int starting_len = xdr->buf->len - 8;
	long len;
	int thislen;
	__be32 nfserr;
	__be32 tmp;
	__be32 *p;
	u32 zzz = 0;
	int pad;

	len = maxcount;
	v = 0;

	thislen = min_t(long, len, ((void *)xdr->end - (void *)xdr->p));
	p = xdr_reserve_space(xdr, (thislen+3)&~3);
	WARN_ON_ONCE(!p);
	resp->rqstp->rq_vec[v].iov_base = p;
	resp->rqstp->rq_vec[v].iov_len = thislen;
	v++;
	len -= thislen;

	while (len) {
		thislen = min_t(long, len, PAGE_SIZE);
		p = xdr_reserve_space(xdr, (thislen+3)&~3);
		WARN_ON_ONCE(!p);
		resp->rqstp->rq_vec[v].iov_base = p;
		resp->rqstp->rq_vec[v].iov_len = thislen;
		v++;
		len -= thislen;
	}
	read->rd_vlen = v;

	len = maxcount;
	nfserr = nfsd_readv(file, read->rd_offset, resp->rqstp->rq_vec,
			read->rd_vlen, &maxcount);
	if (nfserr)
		return nfserr;
	xdr_truncate_encode(xdr, starting_len + 8 + ((maxcount+3)&~3));

	eof = nfsd_eof_on_read(len, maxcount, read->rd_offset,
				d_inode(read->rd_fhp->fh_dentry)->i_size);

	tmp = htonl(eof);
	write_bytes_to_xdr_buf(xdr->buf, starting_len    , &tmp, 4);
	tmp = htonl(maxcount);
	write_bytes_to_xdr_buf(xdr->buf, starting_len + 4, &tmp, 4);

	pad = (maxcount&3) ? 4 - (maxcount&3) : 0;
	write_bytes_to_xdr_buf(xdr->buf, starting_len + 8 + maxcount,
								&zzz, pad);
	return 0;

}
