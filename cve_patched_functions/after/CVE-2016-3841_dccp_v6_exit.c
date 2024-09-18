static void __exit dccp_v6_exit(void)
{
	unregister_pernet_subsys(&dccp_v6_ops);
	inet6_del_protocol(&dccp_v6_protocol, IPPROTO_DCCP);
	inet6_unregister_protosw(&dccp_v6_protosw);
	proto_unregister(&dccp_v6_prot);
}
