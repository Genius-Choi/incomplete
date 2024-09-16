nfsd4_encode_secinfo_no_name(struct nfsd4_compoundres *resp, __be32 nfserr,
		     struct nfsd4_secinfo_no_name *secinfo)
{
	struct xdr_stream *xdr = &resp->xdr;

	return nfsd4_do_encode_secinfo(xdr, nfserr, secinfo->sin_exp);
}
