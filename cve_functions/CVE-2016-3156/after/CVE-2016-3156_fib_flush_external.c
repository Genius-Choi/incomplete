void fib_flush_external(struct net *net)
{
	struct fib_table *tb;
	struct hlist_head *head;
	unsigned int h;

	for (h = 0; h < FIB_TABLE_HASHSZ; h++) {
		head = &net->ipv4.fib_table_hash[h];
		hlist_for_each_entry(tb, head, tb_hlist)
			fib_table_flush_external(tb);
	}
}
