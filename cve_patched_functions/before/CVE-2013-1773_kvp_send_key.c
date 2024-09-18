kvp_send_key(struct work_struct *dummy)
{
	struct cn_msg *msg;
	int index = kvp_transaction.index;

	msg = kzalloc(sizeof(*msg) + sizeof(struct hv_kvp_msg) , GFP_ATOMIC);

	if (msg) {
		msg->id.idx =  CN_KVP_IDX;
		msg->id.val = CN_KVP_VAL;
		msg->seq = KVP_KERNEL_GET;
		((struct hv_ku_msg *)msg->data)->kvp_index = index;
		msg->len = sizeof(struct hv_ku_msg);
		cn_netlink_send(msg, 0, GFP_ATOMIC);
		kfree(msg);
	}
	return;
}
