static void encode_free_stateid(struct xdr_stream *xdr,
				struct nfs41_free_stateid_args *args,
				struct compound_hdr *hdr)
{
	__be32 *p;
	p = reserve_space(xdr, 4 + NFS4_STATEID_SIZE);
	*p++ = cpu_to_be32(OP_FREE_STATEID);
	xdr_encode_opaque_fixed(p, args->stateid->data, NFS4_STATEID_SIZE);
	hdr->nops++;
	hdr->replen += decode_free_stateid_maxsz;
}
