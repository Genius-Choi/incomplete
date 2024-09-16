static int __net_init xt_net_init(struct net *net)
{
	int i;

	for (i = 0; i < NFPROTO_NUMPROTO; i++)
		INIT_LIST_HEAD(&net->xt.tables[i]);
	return 0;
}
