static void encode_lock(struct xdr_stream *xdr, const struct nfs_lock_args *args, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 32);
	*p++ = cpu_to_be32(OP_LOCK);
	*p++ = cpu_to_be32(nfs4_lock_type(args->fl, args->block));
	*p++ = cpu_to_be32(args->reclaim);
	p = xdr_encode_hyper(p, args->fl->fl_start);
	p = xdr_encode_hyper(p, nfs4_lock_length(args->fl));
	*p = cpu_to_be32(args->new_lock_owner);
	if (args->new_lock_owner){
		p = reserve_space(xdr, 4+NFS4_STATEID_SIZE+4);
		*p++ = cpu_to_be32(args->open_seqid->sequence->counter);
		p = xdr_encode_opaque_fixed(p, args->open_stateid->data, NFS4_STATEID_SIZE);
		*p++ = cpu_to_be32(args->lock_seqid->sequence->counter);
		encode_lockowner(xdr, &args->lock_owner);
	}
	else {
		p = reserve_space(xdr, NFS4_STATEID_SIZE+4);
		p = xdr_encode_opaque_fixed(p, args->lock_stateid->data, NFS4_STATEID_SIZE);
		*p = cpu_to_be32(args->lock_seqid->sequence->counter);
	}
	hdr->nops++;
	hdr->replen += decode_lock_maxsz;
}
