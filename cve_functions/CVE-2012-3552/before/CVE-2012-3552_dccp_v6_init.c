static int __init dccp_v6_init(void)
{
	int err = proto_register(&dccp_v6_prot, 1);

	if (err != 0)
		goto out;

	err = inet6_add_protocol(&dccp_v6_protocol, IPPROTO_DCCP);
	if (err != 0)
		goto out_unregister_proto;

	inet6_register_protosw(&dccp_v6_protosw);

	err = register_pernet_subsys(&dccp_v6_ops);
	if (err != 0)
		goto out_destroy_ctl_sock;
out:
	return err;

out_destroy_ctl_sock:
	inet6_del_protocol(&dccp_v6_protocol, IPPROTO_DCCP);
	inet6_unregister_protosw(&dccp_v6_protosw);
out_unregister_proto:
	proto_unregister(&dccp_v6_prot);
	goto out;
}
