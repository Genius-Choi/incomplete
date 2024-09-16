static unsigned int ffs_ep0_poll(struct file *file, poll_table *wait)
{
	struct ffs_data *ffs = file->private_data;
	unsigned int mask = POLLWRNORM;
	int ret;

	poll_wait(file, &ffs->ev.waitq, wait);

	ret = ffs_mutex_lock(&ffs->mutex, file->f_flags & O_NONBLOCK);
	if (unlikely(ret < 0))
		return mask;

	switch (ffs->state) {
	case FFS_READ_DESCRIPTORS:
	case FFS_READ_STRINGS:
		mask |= POLLOUT;
		break;

	case FFS_ACTIVE:
		switch (ffs->setup_state) {
		case FFS_NO_SETUP:
			if (ffs->ev.count)
				mask |= POLLIN;
			break;

		case FFS_SETUP_PENDING:
		case FFS_SETUP_CANCELLED:
			mask |= (POLLIN | POLLOUT);
			break;
		}
	case FFS_CLOSING:
		break;
	case FFS_DEACTIVATED:
		break;
	}

	mutex_unlock(&ffs->mutex);

	return mask;
}
