static int decode_write(struct xdr_stream *xdr, struct nfs_writeres *res)
{
	__be32 *p;
	int status;

	status = decode_op_hdr(xdr, OP_WRITE);
	if (status)
		return status;

	p = xdr_inline_decode(xdr, 16);
	if (unlikely(!p))
		goto out_overflow;
	res->count = be32_to_cpup(p++);
	res->verf->committed = be32_to_cpup(p++);
	memcpy(res->verf->verifier, p, 8);
	return 0;
out_overflow:
	print_overflow_msg(__func__, xdr);
	return -EIO;
}
