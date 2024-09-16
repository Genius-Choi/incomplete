encode_secinfo_no_name(struct xdr_stream *xdr,
		       const struct nfs41_secinfo_no_name_args *args,
		       struct compound_hdr *hdr)
{
	__be32 *p;
	p = reserve_space(xdr, 8);
	*p++ = cpu_to_be32(OP_SECINFO_NO_NAME);
	*p++ = cpu_to_be32(args->style);
	hdr->nops++;
	hdr->replen += decode_secinfo_no_name_maxsz;
	return 0;
}
