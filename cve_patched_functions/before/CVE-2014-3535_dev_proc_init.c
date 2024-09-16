static int __init dev_proc_init(void)
{
	return register_pernet_subsys(&dev_proc_ops);
}
