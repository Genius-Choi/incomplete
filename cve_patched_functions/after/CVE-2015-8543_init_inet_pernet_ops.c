static int __init init_inet_pernet_ops(void)
{
	return register_pernet_subsys(&af_inet_ops);
}
