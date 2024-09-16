static int decode_lock(struct xdr_stream *xdr, struct nfs_lock_res *res)
{
	__be32 *p;
	int status;

	status = decode_op_hdr(xdr, OP_LOCK);
	if (status == -EIO)
		goto out;
	if (status == 0) {
		READ_BUF(NFS4_STATEID_SIZE);
		COPYMEM(res->stateid.data, NFS4_STATEID_SIZE);
	} else if (status == -NFS4ERR_DENIED)
		status = decode_lock_denied(xdr, NULL);
	if (res->open_seqid != NULL)
		nfs_increment_open_seqid(status, res->open_seqid);
	nfs_increment_lock_seqid(status, res->lock_seqid);
out:
	return status;
}
