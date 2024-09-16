static int ip6mr_find_vif(struct mr6_table *mrt, struct net_device *dev)
{
	int ct;

	for (ct = mrt->maxvif - 1; ct >= 0; ct--) {
		if (mrt->vif6_table[ct].dev == dev)
			break;
	}
	return ct;
}
