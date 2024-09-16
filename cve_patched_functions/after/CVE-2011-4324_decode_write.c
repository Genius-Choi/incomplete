static int decode_write(struct xdr_stream *xdr, struct nfs_writeres *res)
{
	__be32 *p;
	int status;

	status = decode_op_hdr(xdr, OP_WRITE);
	if (status)
		return status;

	READ_BUF(16);
	READ32(res->count);
	READ32(res->verf->committed);
	COPYMEM(res->verf->verifier, 8);
	return 0;
}
