static void __exit l2cap_exit(void)
{
	class_remove_file(bt_class, &class_attr_l2cap);

	if (bt_sock_unregister(BTPROTO_L2CAP) < 0)
		BT_ERR("L2CAP socket unregistration failed");

	if (hci_unregister_proto(&l2cap_hci_proto) < 0)
		BT_ERR("L2CAP protocol unregistration failed");

	proto_unregister(&l2cap_proto);
}
