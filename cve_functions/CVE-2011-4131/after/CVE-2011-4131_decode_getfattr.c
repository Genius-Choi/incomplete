static int decode_getfattr(struct xdr_stream *xdr, struct nfs_fattr *fattr,
		const struct nfs_server *server, int may_sleep)
{
	return decode_getfattr_generic(xdr, fattr, NULL, server, may_sleep);
}
