static void encode_close(struct xdr_stream *xdr, const struct nfs_closeargs *arg, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 8+NFS4_STATEID_SIZE);
	*p++ = cpu_to_be32(OP_CLOSE);
	*p++ = cpu_to_be32(arg->seqid->sequence->counter);
	xdr_encode_opaque_fixed(p, arg->stateid->data, NFS4_STATEID_SIZE);
	hdr->nops++;
	hdr->replen += decode_close_maxsz;
}
