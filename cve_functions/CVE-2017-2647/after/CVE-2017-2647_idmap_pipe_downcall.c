idmap_pipe_downcall(struct file *filp, const char __user *src, size_t mlen)
{
	struct rpc_inode *rpci = RPC_I(file_inode(filp));
	struct idmap *idmap = (struct idmap *)rpci->private;
	struct key_construction *cons;
	struct idmap_msg im;
	size_t namelen_in;
	int ret = -ENOKEY;

	/* If instantiation is successful, anyone waiting for key construction
	 * will have been woken up and someone else may now have used
	 * idmap_key_cons - so after this point we may no longer touch it.
	 */
	if (idmap->idmap_upcall_data == NULL)
		goto out_noupcall;

	cons = idmap->idmap_upcall_data->key_cons;

	if (mlen != sizeof(im)) {
		ret = -ENOSPC;
		goto out;
	}

	if (copy_from_user(&im, src, mlen) != 0) {
		ret = -EFAULT;
		goto out;
	}

	if (!(im.im_status & IDMAP_STATUS_SUCCESS)) {
		ret = -ENOKEY;
		goto out;
	}

	namelen_in = strnlen(im.im_name, IDMAP_NAMESZ);
	if (namelen_in == 0 || namelen_in == IDMAP_NAMESZ) {
		ret = -EINVAL;
		goto out;
}

	ret = nfs_idmap_read_and_verify_message(&im,
			&idmap->idmap_upcall_data->idmap_msg,
			cons->key, cons->authkey);
	if (ret >= 0) {
		key_set_timeout(cons->key, nfs_idmap_cache_timeout);
		ret = mlen;
	}

out:
	nfs_idmap_complete_pipe_upcall_locked(idmap, ret);
out_noupcall:
	return ret;
}
