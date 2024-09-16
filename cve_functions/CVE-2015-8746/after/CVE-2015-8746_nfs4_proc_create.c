nfs4_proc_create(struct inode *dir, struct dentry *dentry, struct iattr *sattr,
		 int flags)
{
	struct nfs4_label l, *ilabel = NULL;
	struct nfs_open_context *ctx;
	struct nfs4_state *state;
	int opened = 0;
	int status = 0;

	ctx = alloc_nfs_open_context(dentry, FMODE_READ);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	ilabel = nfs4_label_init_security(dir, dentry, sattr, &l);

	sattr->ia_mode &= ~current_umask();
	state = nfs4_do_open(dir, ctx, flags, sattr, ilabel, &opened);
	if (IS_ERR(state)) {
		status = PTR_ERR(state);
		goto out;
	}
out:
	nfs4_label_release_security(ilabel);
	put_nfs_open_context(ctx);
	return status;
}
