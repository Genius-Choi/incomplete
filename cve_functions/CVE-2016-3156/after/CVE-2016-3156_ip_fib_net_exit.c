static void ip_fib_net_exit(struct net *net)
{
	unsigned int i;

	rtnl_lock();
#ifdef CONFIG_IP_MULTIPLE_TABLES
	RCU_INIT_POINTER(net->ipv4.fib_local, NULL);
	RCU_INIT_POINTER(net->ipv4.fib_main, NULL);
	RCU_INIT_POINTER(net->ipv4.fib_default, NULL);
#endif
	for (i = 0; i < FIB_TABLE_HASHSZ; i++) {
		struct hlist_head *head = &net->ipv4.fib_table_hash[i];
		struct hlist_node *tmp;
		struct fib_table *tb;

		hlist_for_each_entry_safe(tb, tmp, head, tb_hlist) {
			hlist_del(&tb->tb_hlist);
			fib_table_flush(tb);
			fib_free_table(tb);
		}
	}

#ifdef CONFIG_IP_MULTIPLE_TABLES
	fib4_rules_exit(net);
#endif
	rtnl_unlock();
	kfree(net->ipv4.fib_table_hash);
}
