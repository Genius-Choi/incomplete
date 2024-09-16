static int nfs4_xdr_enc_symlink(struct rpc_rqst *req, __be32 *p, const struct nfs4_create_arg *args)
{
	return nfs4_xdr_enc_create(req, p, args);
}
