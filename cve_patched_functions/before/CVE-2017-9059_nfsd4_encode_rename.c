nfsd4_encode_rename(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_rename *rename)
{
	struct xdr_stream *xdr = &resp->xdr;
	__be32 *p;

	if (!nfserr) {
		p = xdr_reserve_space(xdr, 40);
		if (!p)
			return nfserr_resource;
		p = encode_cinfo(p, &rename->rn_sinfo);
		p = encode_cinfo(p, &rename->rn_tinfo);
	}
	return nfserr;
}
