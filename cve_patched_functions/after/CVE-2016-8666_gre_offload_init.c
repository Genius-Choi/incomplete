static int __init gre_offload_init(void)
{
	return inet_add_offload(&gre_offload, IPPROTO_GRE);
}
