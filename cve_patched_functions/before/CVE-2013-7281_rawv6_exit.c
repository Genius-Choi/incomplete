void rawv6_exit(void)
{
	inet6_unregister_protosw(&rawv6_protosw);
}
