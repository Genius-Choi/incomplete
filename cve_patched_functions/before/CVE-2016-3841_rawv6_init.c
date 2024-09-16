int __init rawv6_init(void)
{
	return inet6_register_protosw(&rawv6_protosw);
}
