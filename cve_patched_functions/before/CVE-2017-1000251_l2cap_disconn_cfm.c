static int l2cap_disconn_cfm(struct hci_conn *hcon, u8 reason)
{
	BT_DBG("hcon %p reason %d", hcon, reason);

	if (hcon->type != ACL_LINK)
		return 0;

	l2cap_conn_del(hcon, bt_err(reason));

	return 0;
}
