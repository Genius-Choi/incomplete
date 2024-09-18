static int encode_readdir(struct xdr_stream *xdr, const struct nfs4_readdir_arg *readdir, struct rpc_rqst *req)
{
	uint32_t attrs[2] = {
		FATTR4_WORD0_RDATTR_ERROR|FATTR4_WORD0_FILEID,
		FATTR4_WORD1_MOUNTED_ON_FILEID,
	};
	__be32 *p;

	RESERVE_SPACE(12+NFS4_VERIFIER_SIZE+20);
	WRITE32(OP_READDIR);
	WRITE64(readdir->cookie);
	WRITEMEM(readdir->verifier.data, NFS4_VERIFIER_SIZE);
	WRITE32(readdir->count >> 1);  /* We're not doing readdirplus */
	WRITE32(readdir->count);
	WRITE32(2);
	/* Switch to mounted_on_fileid if the server supports it */
	if (readdir->bitmask[1] & FATTR4_WORD1_MOUNTED_ON_FILEID)
		attrs[0] &= ~FATTR4_WORD0_FILEID;
	else
		attrs[1] &= ~FATTR4_WORD1_MOUNTED_ON_FILEID;
	WRITE32(attrs[0] & readdir->bitmask[0]);
	WRITE32(attrs[1] & readdir->bitmask[1]);
	dprintk("%s: cookie = %Lu, verifier = %08x:%08x, bitmap = %08x:%08x\n",
			__func__,
			(unsigned long long)readdir->cookie,
			((u32 *)readdir->verifier.data)[0],
			((u32 *)readdir->verifier.data)[1],
			attrs[0] & readdir->bitmask[0],
			attrs[1] & readdir->bitmask[1]);

	return 0;
}
