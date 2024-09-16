static int check_target(struct ip6t_entry *e, struct net *net, const char *name)
{
	struct xt_entry_target *t = ip6t_get_target(e);
	struct xt_tgchk_param par = {
		.net       = net,
		.table     = name,
		.entryinfo = e,
		.target    = t->u.kernel.target,
		.targinfo  = t->data,
		.hook_mask = e->comefrom,
		.family    = NFPROTO_IPV6,
	};
	int ret;

	t = ip6t_get_target(e);
	ret = xt_check_target(&par, t->u.target_size - sizeof(*t),
	      e->ipv6.proto, e->ipv6.invflags & IP6T_INV_PROTO);
	if (ret < 0) {
		duprintf("ip_tables: check failed for `%s'.\n",
			 t->u.kernel.target->name);
		return ret;
	}
	return 0;
}
