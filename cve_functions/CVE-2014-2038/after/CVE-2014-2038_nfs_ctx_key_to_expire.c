bool nfs_ctx_key_to_expire(struct nfs_open_context *ctx)
{
	return rpcauth_cred_key_to_expire(ctx->cred);
}
