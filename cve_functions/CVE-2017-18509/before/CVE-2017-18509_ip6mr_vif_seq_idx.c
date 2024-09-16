static struct mif_device *ip6mr_vif_seq_idx(struct net *net,
					    struct ipmr_vif_iter *iter,
					    loff_t pos)
{
	struct mr6_table *mrt = iter->mrt;

	for (iter->ct = 0; iter->ct < mrt->maxvif; ++iter->ct) {
		if (!MIF_EXISTS(mrt, iter->ct))
			continue;
		if (pos-- == 0)
			return &mrt->vif6_table[iter->ct];
	}
	return NULL;
}
