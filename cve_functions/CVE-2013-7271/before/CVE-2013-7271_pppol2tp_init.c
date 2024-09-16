static int __init pppol2tp_init(void)
{
	int err;

	err = register_pernet_device(&pppol2tp_net_ops);
	if (err)
		goto out;

	err = proto_register(&pppol2tp_sk_proto, 0);
	if (err)
		goto out_unregister_pppol2tp_pernet;

	err = register_pppox_proto(PX_PROTO_OL2TP, &pppol2tp_proto);
	if (err)
		goto out_unregister_pppol2tp_proto;

#ifdef CONFIG_L2TP_V3
	err = l2tp_nl_register_ops(L2TP_PWTYPE_PPP, &pppol2tp_nl_cmd_ops);
	if (err)
		goto out_unregister_pppox;
#endif

	pr_info("PPPoL2TP kernel driver, %s\n", PPPOL2TP_DRV_VERSION);

out:
	return err;

#ifdef CONFIG_L2TP_V3
out_unregister_pppox:
	unregister_pppox_proto(PX_PROTO_OL2TP);
#endif
out_unregister_pppol2tp_proto:
	proto_unregister(&pppol2tp_sk_proto);
out_unregister_pppol2tp_pernet:
	unregister_pernet_device(&pppol2tp_net_ops);
	goto out;
}
