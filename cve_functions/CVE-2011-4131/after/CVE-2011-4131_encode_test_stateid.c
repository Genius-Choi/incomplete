static void encode_test_stateid(struct xdr_stream *xdr,
				struct nfs41_test_stateid_args *args,
				struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 8 + NFS4_STATEID_SIZE);
	*p++ = cpu_to_be32(OP_TEST_STATEID);
	*p++ = cpu_to_be32(1);
	xdr_encode_opaque_fixed(p, args->stateid->data, NFS4_STATEID_SIZE);
	hdr->nops++;
	hdr->replen += decode_test_stateid_maxsz;
}
