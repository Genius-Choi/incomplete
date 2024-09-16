nfsd4_encode_layoutcommit(struct nfsd4_compoundres *resp, __be32 nfserr,
			  struct nfsd4_layoutcommit *lcp)
{
	struct xdr_stream *xdr = &resp->xdr;
	__be32 *p;

	if (nfserr)
		return nfserr;

	p = xdr_reserve_space(xdr, 4);
	if (!p)
		return nfserr_resource;
	*p++ = cpu_to_be32(lcp->lc_size_chg);
	if (lcp->lc_size_chg) {
		p = xdr_reserve_space(xdr, 8);
		if (!p)
			return nfserr_resource;
		p = xdr_encode_hyper(p, lcp->lc_newsize);
	}

	return nfs_ok;
}
