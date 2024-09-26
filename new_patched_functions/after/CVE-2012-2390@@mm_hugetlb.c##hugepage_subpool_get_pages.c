static int hugepage_subpool_get_pages(struct hugepage_subpool *spool,
				      long delta)
{
	int ret = 0;

	if (!spool)
		return 0;

	spin_lock(&spool->lock);
	if ((spool->used_hpages + delta) <= spool->max_hpages) {
		spool->used_hpages += delta;
	} else {
		ret = -ENOMEM;
	}
	spin_unlock(&spool->lock);

	return ret;
}
