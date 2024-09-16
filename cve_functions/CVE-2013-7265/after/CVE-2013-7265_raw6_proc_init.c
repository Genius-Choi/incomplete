int __init raw6_proc_init(void)
{
	return register_pernet_subsys(&raw6_net_ops);
}
