static int __init l2cap_init(void)
{
	int err;

	err = proto_register(&l2cap_proto, 0);
	if (err < 0)
		return err;

	err = bt_sock_register(BTPROTO_L2CAP, &l2cap_sock_family_ops);
	if (err < 0) {
		BT_ERR("L2CAP socket registration failed");
		goto error;
	}

	err = hci_register_proto(&l2cap_hci_proto);
	if (err < 0) {
		BT_ERR("L2CAP protocol registration failed");
		bt_sock_unregister(BTPROTO_L2CAP);
		goto error;
	}

	if (class_create_file(bt_class, &class_attr_l2cap) < 0)
		BT_ERR("Failed to create L2CAP info file");

	BT_INFO("L2CAP ver %s", VERSION);
	BT_INFO("L2CAP socket layer initialized");

	return 0;

error:
	proto_unregister(&l2cap_proto);
	return err;
}
