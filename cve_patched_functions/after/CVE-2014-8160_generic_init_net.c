static int generic_init_net(struct net *net, u_int16_t proto)
{
	int ret;
	struct nf_generic_net *gn = generic_pernet(net);
	struct nf_proto_net *pn = &gn->pn;

	gn->timeout = nf_ct_generic_timeout;

	ret = generic_kmemdup_compat_sysctl_table(pn, gn);
	if (ret < 0)
		return ret;

	ret = generic_kmemdup_sysctl_table(pn, gn);
	if (ret < 0)
		nf_ct_kfree_compat_sysctl_table(pn);

	return ret;
}
