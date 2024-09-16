static int encode_lock(struct xdr_stream *xdr, const struct nfs_lock_args *args)
{
	__be32 *p;

	RESERVE_SPACE(32);
	WRITE32(OP_LOCK);
	WRITE32(nfs4_lock_type(args->fl, args->block));
	WRITE32(args->reclaim);
	WRITE64(args->fl->fl_start);
	WRITE64(nfs4_lock_length(args->fl));
	WRITE32(args->new_lock_owner);
	if (args->new_lock_owner){
		RESERVE_SPACE(4+NFS4_STATEID_SIZE+32);
		WRITE32(args->open_seqid->sequence->counter);
		WRITEMEM(args->open_stateid->data, NFS4_STATEID_SIZE);
		WRITE32(args->lock_seqid->sequence->counter);
		WRITE64(args->lock_owner.clientid);
		WRITE32(16);
		WRITEMEM("lock id:", 8);
		WRITE64(args->lock_owner.id);
	}
	else {
		RESERVE_SPACE(NFS4_STATEID_SIZE+4);
		WRITEMEM(args->lock_stateid->data, NFS4_STATEID_SIZE);
		WRITE32(args->lock_seqid->sequence->counter);
	}

	return 0;
}
