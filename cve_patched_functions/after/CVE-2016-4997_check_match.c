static int check_match(struct xt_entry_match *m, struct xt_mtchk_param *par)
{
	const struct ip6t_ip6 *ipv6 = par->entryinfo;
	int ret;

	par->match     = m->u.kernel.match;
	par->matchinfo = m->data;

	ret = xt_check_match(par, m->u.match_size - sizeof(*m),
			     ipv6->proto, ipv6->invflags & IP6T_INV_PROTO);
	if (ret < 0) {
		duprintf("ip_tables: check failed for `%s'.\n",
			 par.match->name);
		return ret;
	}
	return 0;
}
