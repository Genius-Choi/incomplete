nfsd4_encode_copy(struct nfsd4_compoundres *resp, __be32 nfserr,
		  struct nfsd4_copy *copy)
{
	__be32 *p;

	if (!nfserr) {
		nfserr = nfsd42_encode_write_res(resp, &copy->cp_res);
		if (nfserr)
			return nfserr;

		p = xdr_reserve_space(&resp->xdr, 4 + 4);
		*p++ = cpu_to_be32(copy->cp_consecutive);
		*p++ = cpu_to_be32(copy->cp_synchronous);
	}
	return nfserr;
}
