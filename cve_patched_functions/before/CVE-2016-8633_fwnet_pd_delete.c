static void fwnet_pd_delete(struct fwnet_partial_datagram *old)
{
	struct fwnet_fragment_info *fi, *n;

	list_for_each_entry_safe(fi, n, &old->fi_list, fi_link)
		kfree(fi);

	list_del(&old->pd_link);
	dev_kfree_skb_any(old->skb);
	kfree(old);
}
