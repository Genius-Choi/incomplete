static void __exit pppol2tp_exit(void)
{
#ifdef CONFIG_L2TP_V3
	l2tp_nl_unregister_ops(L2TP_PWTYPE_PPP);
#endif
	unregister_pppox_proto(PX_PROTO_OL2TP);
	proto_unregister(&pppol2tp_sk_proto);
	unregister_pernet_device(&pppol2tp_net_ops);
}
