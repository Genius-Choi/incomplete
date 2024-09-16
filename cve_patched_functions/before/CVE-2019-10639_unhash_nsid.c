static void unhash_nsid(struct net *net, struct net *last)
{
	struct net *tmp;
	/* This function is only called from cleanup_net() work,
	 * and this work is the only process, that may delete
	 * a net from net_namespace_list. So, when the below
	 * is executing, the list may only grow. Thus, we do not
	 * use for_each_net_rcu() or net_rwsem.
	 */
	for_each_net(tmp) {
		int id;

		spin_lock_bh(&tmp->nsid_lock);
		id = __peernet2id(tmp, net);
		if (id >= 0)
			idr_remove(&tmp->netns_ids, id);
		spin_unlock_bh(&tmp->nsid_lock);
		if (id >= 0)
			rtnl_net_notifyid(tmp, RTM_DELNSID, id);
		if (tmp == last)
			break;
	}
	spin_lock_bh(&net->nsid_lock);
	idr_destroy(&net->netns_ids);
	spin_unlock_bh(&net->nsid_lock);
}
