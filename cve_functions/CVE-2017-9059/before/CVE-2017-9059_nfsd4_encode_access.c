nfsd4_encode_access(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_access *access)
{
	struct xdr_stream *xdr = &resp->xdr;
	__be32 *p;

	if (!nfserr) {
		p = xdr_reserve_space(xdr, 8);
		if (!p)
			return nfserr_resource;
		*p++ = cpu_to_be32(access->ac_supported);
		*p++ = cpu_to_be32(access->ac_resp_access);
	}
	return nfserr;
}
