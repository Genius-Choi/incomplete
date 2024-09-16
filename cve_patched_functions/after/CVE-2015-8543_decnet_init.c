static int __init decnet_init(void)
{
	int rc;

	printk(banner);

	rc = proto_register(&dn_proto, 1);
	if (rc != 0)
		goto out;

	dn_neigh_init();
	dn_dev_init();
	dn_route_init();
	dn_fib_init();

	sock_register(&dn_family_ops);
	dev_add_pack(&dn_dix_packet_type);
	register_netdevice_notifier(&dn_dev_notifier);

	proc_create("decnet", S_IRUGO, init_net.proc_net, &dn_socket_seq_fops);
	dn_register_sysctl();
out:
	return rc;

}
