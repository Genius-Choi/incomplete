nlmsvc_cancel_blocked(struct net *net, struct nlm_file *file, struct nlm_lock *lock)
{
	struct nlm_block	*block;
	int status = 0;

	dprintk("lockd: nlmsvc_cancel(%s/%ld, pi=%d, %Ld-%Ld)\n",
				file_inode(file->f_file)->i_sb->s_id,
				file_inode(file->f_file)->i_ino,
				lock->fl.fl_pid,
				(long long)lock->fl.fl_start,
				(long long)lock->fl.fl_end);

	if (locks_in_grace(net))
		return nlm_lck_denied_grace_period;

	mutex_lock(&file->f_mutex);
	block = nlmsvc_lookup_block(file, lock);
	mutex_unlock(&file->f_mutex);
	if (block != NULL) {
		vfs_cancel_lock(block->b_file->f_file,
				&block->b_call->a_args.lock.fl);
		status = nlmsvc_unlink_block(block);
		nlmsvc_release_block(block);
	}
	return status ? nlm_lck_denied : nlm_granted;
}
