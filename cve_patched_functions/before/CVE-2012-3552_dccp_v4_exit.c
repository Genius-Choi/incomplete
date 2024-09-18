static void __exit dccp_v4_exit(void)
{
	unregister_pernet_subsys(&dccp_v4_ops);
	inet_unregister_protosw(&dccp_v4_protosw);
	inet_del_protocol(&dccp_v4_protocol, IPPROTO_DCCP);
	proto_unregister(&dccp_v4_prot);
}
