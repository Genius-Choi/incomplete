const char *get_link(struct nameidata *nd)
{
	struct saved *last = nd->stack + nd->depth - 1;
	struct dentry *dentry = last->link.dentry;
	struct inode *inode = last->inode;
	int error;
	const char *res;

	if (!(nd->flags & LOOKUP_RCU)) {
		touch_atime(&last->link);
		cond_resched();
	} else if (atime_needs_update(&last->link, inode)) {
		if (unlikely(unlazy_walk(nd, NULL, 0)))
			return ERR_PTR(-ECHILD);
		touch_atime(&last->link);
	}

	error = security_inode_follow_link(dentry, inode,
					   nd->flags & LOOKUP_RCU);
	if (unlikely(error))
		return ERR_PTR(error);

	nd->last_type = LAST_BIND;
	res = inode->i_link;
	if (!res) {
		if (nd->flags & LOOKUP_RCU) {
			if (unlikely(unlazy_walk(nd, NULL, 0)))
				return ERR_PTR(-ECHILD);
		}
		res = inode->i_op->follow_link(dentry, &last->cookie);
		if (IS_ERR_OR_NULL(res)) {
			last->cookie = NULL;
			return res;
		}
	}
	if (*res == '/') {
		if (nd->flags & LOOKUP_RCU) {
			struct dentry *d;
			if (!nd->root.mnt)
				set_root_rcu(nd);
			nd->path = nd->root;
			d = nd->path.dentry;
			nd->inode = d->d_inode;
			nd->seq = nd->root_seq;
			if (unlikely(read_seqcount_retry(&d->d_seq, nd->seq)))
				return ERR_PTR(-ECHILD);
		} else {
			if (!nd->root.mnt)
				set_root(nd);
			path_put(&nd->path);
			nd->path = nd->root;
			path_get(&nd->root);
			nd->inode = nd->path.dentry->d_inode;
		}
		nd->flags |= LOOKUP_JUMPED;
		while (unlikely(*++res == '/'))
			;
	}
	if (!*res)
		res = NULL;
	return res;
}
