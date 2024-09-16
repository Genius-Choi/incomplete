nfsd4_encode_getfh(struct nfsd4_compoundres *resp, __be32 nfserr, struct svc_fh **fhpp)
{
	struct xdr_stream *xdr = &resp->xdr;
	struct svc_fh *fhp = *fhpp;
	unsigned int len;
	__be32 *p;

	if (!nfserr) {
		len = fhp->fh_handle.fh_size;
		p = xdr_reserve_space(xdr, len + 4);
		if (!p)
			return nfserr_resource;
		p = xdr_encode_opaque(p, &fhp->fh_handle.fh_base, len);
	}
	return nfserr;
}
