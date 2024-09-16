static struct mfc6_cache *ipmr_mfc_seq_idx(struct net *net,
					   struct ipmr_mfc_iter *it, loff_t pos)
{
	struct mr6_table *mrt = it->mrt;
	struct mfc6_cache *mfc;

	read_lock(&mrt_lock);
	for (it->ct = 0; it->ct < MFC6_LINES; it->ct++) {
		it->cache = &mrt->mfc6_cache_array[it->ct];
		list_for_each_entry(mfc, it->cache, list)
			if (pos-- == 0)
				return mfc;
	}
	read_unlock(&mrt_lock);

	spin_lock_bh(&mfc_unres_lock);
	it->cache = &mrt->mfc6_unres_queue;
	list_for_each_entry(mfc, it->cache, list)
		if (pos-- == 0)
			return mfc;
	spin_unlock_bh(&mfc_unres_lock);

	it->cache = NULL;
	return NULL;
}
