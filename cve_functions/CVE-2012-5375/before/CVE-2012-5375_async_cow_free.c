static noinline void async_cow_free(struct btrfs_work *work)
{
	struct async_cow *async_cow;
	async_cow = container_of(work, struct async_cow, work);
	if (async_cow->inode)
		btrfs_add_delayed_iput(async_cow->inode);
	kfree(async_cow);
}
