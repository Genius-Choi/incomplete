ffs_setup_state_clear_cancelled(struct ffs_data *ffs)
{
	return (enum ffs_setup_state)
		cmpxchg(&ffs->setup_state, FFS_SETUP_CANCELLED, FFS_NO_SETUP);
}
