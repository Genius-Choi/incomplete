static void ipmr_mfc_seq_stop(struct seq_file *seq, void *v)
{
	struct ipmr_mfc_iter *it = seq->private;
	struct mr6_table *mrt = it->mrt;

	if (it->cache == &mrt->mfc6_unres_queue)
		spin_unlock_bh(&mfc_unres_lock);
	else if (it->cache == &mrt->mfc6_cache_array[it->ct])
		read_unlock(&mrt_lock);
}
