static struct nfs_open_context *alloc_nfs_open_context(struct vfsmount *mnt, struct dentry *dentry, struct rpc_cred *cred)
{
	struct nfs_open_context *ctx;

	ctx = kmalloc(sizeof(*ctx), GFP_KERNEL);
	if (ctx != NULL) {
		ctx->path.dentry = dget(dentry);
		ctx->path.mnt = mntget(mnt);
		ctx->cred = get_rpccred(cred);
		ctx->state = NULL;
		ctx->lockowner = current->files;
		ctx->flags = 0;
		ctx->error = 0;
		ctx->dir_cookie = 0;
		atomic_set(&ctx->count, 1);
	}
	return ctx;
}
