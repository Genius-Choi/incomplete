void ebt_unregister_table(struct net *net, struct ebt_table *table,
			  const struct nf_hook_ops *ops)
{
	if (ops)
		nf_unregister_net_hooks(net, ops, hweight32(table->valid_hooks));
	__ebt_unregister_table(net, table);
}
