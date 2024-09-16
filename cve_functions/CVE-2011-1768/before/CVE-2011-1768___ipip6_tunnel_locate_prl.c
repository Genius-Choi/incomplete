__ipip6_tunnel_locate_prl(struct ip_tunnel *t, __be32 addr)
{
	struct ip_tunnel_prl_entry *prl;

	for_each_prl_rcu(t->prl)
		if (prl->addr == addr)
			break;
	return prl;

}
