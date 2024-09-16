int __init icmp_init(void)
{
	return register_pernet_subsys(&icmp_sk_ops);
}
