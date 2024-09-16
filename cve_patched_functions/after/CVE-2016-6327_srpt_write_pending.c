static int srpt_write_pending(struct se_cmd *se_cmd)
{
	struct srpt_rdma_ch *ch;
	struct srpt_send_ioctx *ioctx;
	enum srpt_command_state new_state;
	enum rdma_ch_state ch_state;
	int ret;

	ioctx = container_of(se_cmd, struct srpt_send_ioctx, cmd);

	new_state = srpt_set_cmd_state(ioctx, SRPT_STATE_NEED_DATA);
	WARN_ON(new_state == SRPT_STATE_DONE);

	ch = ioctx->ch;
	BUG_ON(!ch);

	ch_state = srpt_get_ch_state(ch);
	switch (ch_state) {
	case CH_CONNECTING:
		WARN(true, "unexpected channel state %d\n", ch_state);
		ret = -EINVAL;
		goto out;
	case CH_LIVE:
		break;
	case CH_DISCONNECTING:
	case CH_DRAINING:
	case CH_RELEASING:
		pr_debug("cmd with tag %lld: channel disconnecting\n",
			 ioctx->cmd.tag);
		srpt_set_cmd_state(ioctx, SRPT_STATE_DATA_IN);
		ret = -EINVAL;
		goto out;
	}
	ret = srpt_xfer_data(ch, ioctx);

out:
	return ret;
}
