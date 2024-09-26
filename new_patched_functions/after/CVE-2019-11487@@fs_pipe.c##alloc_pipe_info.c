struct pipe_inode_info *alloc_pipe_info(void)
{
	struct pipe_inode_info *pipe;
	unsigned long pipe_bufs = PIPE_DEF_BUFFERS;
	struct user_struct *user = get_current_user();
	unsigned long user_bufs;
	unsigned int max_size = READ_ONCE(pipe_max_size);

	pipe = kzalloc(sizeof(struct pipe_inode_info), GFP_KERNEL_ACCOUNT);
	if (pipe == NULL)
		goto out_free_uid;

	if (pipe_bufs * PAGE_SIZE > max_size && !capable(CAP_SYS_RESOURCE))
		pipe_bufs = max_size >> PAGE_SHIFT;

	user_bufs = account_pipe_buffers(user, 0, pipe_bufs);

	if (too_many_pipe_buffers_soft(user_bufs) && is_unprivileged_user()) {
		user_bufs = account_pipe_buffers(user, pipe_bufs, 1);
		pipe_bufs = 1;
	}

	if (too_many_pipe_buffers_hard(user_bufs) && is_unprivileged_user())
		goto out_revert_acct;

	pipe->bufs = kcalloc(pipe_bufs, sizeof(struct pipe_buffer),
			     GFP_KERNEL_ACCOUNT);

	if (pipe->bufs) {
		init_waitqueue_head(&pipe->wait);
		pipe->r_counter = pipe->w_counter = 1;
		pipe->buffers = pipe_bufs;
		pipe->user = user;
		mutex_init(&pipe->mutex);
		return pipe;
	}

out_revert_acct:
	(void) account_pipe_buffers(user, pipe_bufs, 0);
	kfree(pipe);
out_free_uid:
	free_uid(user);
	return NULL;
}
