static int srpt_write_pending_status(struct se_cmd *se_cmd)
{
	struct srpt_send_ioctx *ioctx;

	ioctx = container_of(se_cmd, struct srpt_send_ioctx, cmd);
	return srpt_get_cmd_state(ioctx) == SRPT_STATE_NEED_DATA;
}
