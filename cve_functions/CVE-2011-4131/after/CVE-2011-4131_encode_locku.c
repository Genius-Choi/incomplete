static void encode_locku(struct xdr_stream *xdr, const struct nfs_locku_args *args, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 12+NFS4_STATEID_SIZE+16);
	*p++ = cpu_to_be32(OP_LOCKU);
	*p++ = cpu_to_be32(nfs4_lock_type(args->fl, 0));
	*p++ = cpu_to_be32(args->seqid->sequence->counter);
	p = xdr_encode_opaque_fixed(p, args->stateid->data, NFS4_STATEID_SIZE);
	p = xdr_encode_hyper(p, args->fl->fl_start);
	xdr_encode_hyper(p, nfs4_lock_length(args->fl));
	hdr->nops++;
	hdr->replen += decode_locku_maxsz;
}
