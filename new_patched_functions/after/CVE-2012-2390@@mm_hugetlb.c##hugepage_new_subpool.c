struct hugepage_subpool *hugepage_new_subpool(long nr_blocks)
{
	struct hugepage_subpool *spool;

	spool = kmalloc(sizeof(*spool), GFP_KERNEL);
	if (!spool)
		return NULL;

	spin_lock_init(&spool->lock);
	spool->count = 1;
	spool->max_hpages = nr_blocks;
	spool->used_hpages = 0;

	return spool;
}
