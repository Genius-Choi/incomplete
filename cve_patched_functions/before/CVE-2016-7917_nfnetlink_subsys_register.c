int nfnetlink_subsys_register(const struct nfnetlink_subsystem *n)
{
	nfnl_lock(n->subsys_id);
	if (table[n->subsys_id].subsys) {
		nfnl_unlock(n->subsys_id);
		return -EBUSY;
	}
	rcu_assign_pointer(table[n->subsys_id].subsys, n);
	nfnl_unlock(n->subsys_id);

	return 0;
}
