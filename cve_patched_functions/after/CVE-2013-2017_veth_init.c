static __init int veth_init(void)
{
	return rtnl_link_register(&veth_link_ops);
}
