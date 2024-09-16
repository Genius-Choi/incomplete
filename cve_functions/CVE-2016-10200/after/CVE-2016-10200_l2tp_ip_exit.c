static void __exit l2tp_ip_exit(void)
{
	inet_unregister_protosw(&l2tp_ip_protosw);
	inet_del_protocol(&l2tp_ip_protocol, IPPROTO_L2TP);
	proto_unregister(&l2tp_ip_prot);
}
