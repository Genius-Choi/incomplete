struct fib_table *fib_new_table(struct net *net, u32 id)
{
	struct fib_table *tb, *alias = NULL;
	unsigned int h;

	if (id == 0)
		id = RT_TABLE_MAIN;
	tb = fib_get_table(net, id);
	if (tb)
		return tb;

	if (id == RT_TABLE_LOCAL)
		alias = fib_new_table(net, RT_TABLE_MAIN);

	tb = fib_trie_table(id, alias);
	if (!tb)
		return NULL;

	switch (id) {
	case RT_TABLE_LOCAL:
		rcu_assign_pointer(net->ipv4.fib_local, tb);
		break;
	case RT_TABLE_MAIN:
		rcu_assign_pointer(net->ipv4.fib_main, tb);
		break;
	case RT_TABLE_DEFAULT:
		rcu_assign_pointer(net->ipv4.fib_default, tb);
		break;
	default:
		break;
	}

	h = id & (FIB_TABLE_HASHSZ - 1);
	hlist_add_head_rcu(&tb->tb_hlist, &net->ipv4.fib_table_hash[h]);
	return tb;
}
