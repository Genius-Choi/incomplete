static int decode_setclientid(struct xdr_stream *xdr, struct nfs_client *clp)
{
	__be32 *p;
	uint32_t opnum;
	int32_t nfserr;

	READ_BUF(8);
	READ32(opnum);
	if (opnum != OP_SETCLIENTID) {
		dprintk("nfs: decode_setclientid: Server returned operation"
			       	" %d\n", opnum);
		return -EIO;
	}
	READ32(nfserr);
	if (nfserr == NFS_OK) {
		READ_BUF(8 + NFS4_VERIFIER_SIZE);
		READ64(clp->cl_clientid);
		COPYMEM(clp->cl_confirm.data, NFS4_VERIFIER_SIZE);
	} else if (nfserr == NFSERR_CLID_INUSE) {
		uint32_t len;

		/* skip netid string */
		READ_BUF(4);
		READ32(len);
		READ_BUF(len);

		/* skip uaddr string */
		READ_BUF(4);
		READ32(len);
		READ_BUF(len);
		return -NFSERR_CLID_INUSE;
	} else
		return nfs4_stat_to_errno(nfserr);

	return 0;
}
