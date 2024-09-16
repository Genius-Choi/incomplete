static void srpt_aborted_task(struct se_cmd *cmd)
{
	struct srpt_send_ioctx *ioctx = container_of(cmd,
				struct srpt_send_ioctx, cmd);

	srpt_unmap_sg_to_ib_sge(ioctx->ch, ioctx);
}
