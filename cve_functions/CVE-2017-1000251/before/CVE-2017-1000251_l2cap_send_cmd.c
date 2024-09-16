static inline int l2cap_send_cmd(struct l2cap_conn *conn, u8 ident, u8 code, u16 len, void *data)
{
	struct sk_buff *skb = l2cap_build_cmd(conn, code, ident, len, data);

	BT_DBG("code 0x%2.2x", code);

	if (!skb)
		return -ENOMEM;

	return hci_send_acl(conn->hcon, skb, 0);
}
