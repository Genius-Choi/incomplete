static void __devinet_sysctl_unregister(struct ipv4_devconf *cnf)
{
	struct devinet_sysctl_table *t = cnf->sysctl;

	if (!t)
		return;

	cnf->sysctl = NULL;
	unregister_net_sysctl_table(t->sysctl_header);
	kfree(t);
}
