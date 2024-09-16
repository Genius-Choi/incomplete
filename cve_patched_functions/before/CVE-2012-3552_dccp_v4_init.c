static int __init dccp_v4_init(void)
{
	int err = proto_register(&dccp_v4_prot, 1);

	if (err != 0)
		goto out;

	err = inet_add_protocol(&dccp_v4_protocol, IPPROTO_DCCP);
	if (err != 0)
		goto out_proto_unregister;

	inet_register_protosw(&dccp_v4_protosw);

	err = register_pernet_subsys(&dccp_v4_ops);
	if (err)
		goto out_destroy_ctl_sock;
out:
	return err;
out_destroy_ctl_sock:
	inet_unregister_protosw(&dccp_v4_protosw);
	inet_del_protocol(&dccp_v4_protocol, IPPROTO_DCCP);
out_proto_unregister:
	proto_unregister(&dccp_v4_prot);
	goto out;
}
