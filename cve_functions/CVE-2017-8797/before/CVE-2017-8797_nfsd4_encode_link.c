nfsd4_encode_link(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_link *link)
{
	struct xdr_stream *xdr = &resp->xdr;
	__be32 *p;

	if (!nfserr) {
		p = xdr_reserve_space(xdr, 20);
		if (!p)
			return nfserr_resource;
		p = encode_cinfo(p, &link->li_cinfo);
	}
	return nfserr;
}
