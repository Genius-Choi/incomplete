static void encode_open_downgrade(struct xdr_stream *xdr, const struct nfs_closeargs *arg, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 4+NFS4_STATEID_SIZE+4);
	*p++ = cpu_to_be32(OP_OPEN_DOWNGRADE);
	p = xdr_encode_opaque_fixed(p, arg->stateid->data, NFS4_STATEID_SIZE);
	*p = cpu_to_be32(arg->seqid->sequence->counter);
	encode_share_access(xdr, arg->fmode);
	hdr->nops++;
	hdr->replen += decode_open_downgrade_maxsz;
}
