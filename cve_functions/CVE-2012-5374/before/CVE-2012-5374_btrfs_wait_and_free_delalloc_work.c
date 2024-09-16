void btrfs_wait_and_free_delalloc_work(struct btrfs_delalloc_work *work)
{
	wait_for_completion(&work->completion);
	kmem_cache_free(btrfs_delalloc_work_cachep, work);
}
