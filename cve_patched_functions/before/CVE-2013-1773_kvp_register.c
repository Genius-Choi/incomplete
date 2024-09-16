kvp_register(void)
{

	struct cn_msg *msg;

	msg = kzalloc(sizeof(*msg) + strlen(HV_DRV_VERSION) + 1 , GFP_ATOMIC);

	if (msg) {
		msg->id.idx =  CN_KVP_IDX;
		msg->id.val = CN_KVP_VAL;
		msg->seq = KVP_REGISTER;
		strcpy(msg->data, HV_DRV_VERSION);
		msg->len = strlen(HV_DRV_VERSION) + 1;
		cn_netlink_send(msg, 0, GFP_ATOMIC);
		kfree(msg);
	}
}
