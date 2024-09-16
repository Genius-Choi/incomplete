static int airo_set_wap(struct net_device *dev,
			struct iw_request_info *info,
			struct sockaddr *awrq,
			char *extra)
{
	struct airo_info *local = dev->ml_priv;
	Cmd cmd;
	Resp rsp;
	APListRid APList_rid;
	static const u8 any[ETH_ALEN] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	static const u8 off[ETH_ALEN] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	if (awrq->sa_family != ARPHRD_ETHER)
		return -EINVAL;
	else if (!memcmp(any, awrq->sa_data, ETH_ALEN) ||
	         !memcmp(off, awrq->sa_data, ETH_ALEN)) {
		memset(&cmd, 0, sizeof(cmd));
		cmd.cmd=CMD_LOSE_SYNC;
		if (down_interruptible(&local->sem))
			return -ERESTARTSYS;
		issuecommand(local, &cmd, &rsp);
		up(&local->sem);
	} else {
		memset(&APList_rid, 0, sizeof(APList_rid));
		APList_rid.len = cpu_to_le16(sizeof(APList_rid));
		memcpy(APList_rid.ap[0], awrq->sa_data, ETH_ALEN);
		disable_MAC(local, 1);
		writeAPListRid(local, &APList_rid, 1);
		enable_MAC(local, 1);
	}
	return 0;
}
