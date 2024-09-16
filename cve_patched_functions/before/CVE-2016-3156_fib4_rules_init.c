static int __net_init fib4_rules_init(struct net *net)
{
	struct fib_table *local_table, *main_table;

	main_table  = fib_trie_table(RT_TABLE_MAIN, NULL);
	if (!main_table)
		return -ENOMEM;

	local_table = fib_trie_table(RT_TABLE_LOCAL, main_table);
	if (!local_table)
		goto fail;

	hlist_add_head_rcu(&local_table->tb_hlist,
				&net->ipv4.fib_table_hash[TABLE_LOCAL_INDEX]);
	hlist_add_head_rcu(&main_table->tb_hlist,
				&net->ipv4.fib_table_hash[TABLE_MAIN_INDEX]);
	return 0;

fail:
	fib_free_table(main_table);
	return -ENOMEM;
}
