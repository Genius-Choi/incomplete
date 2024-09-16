static void srpt_handle_new_iu(struct srpt_rdma_ch *ch,
			       struct srpt_recv_ioctx *recv_ioctx,
			       struct srpt_send_ioctx *send_ioctx)
{
	struct srp_cmd *srp_cmd;
	enum rdma_ch_state ch_state;

	BUG_ON(!ch);
	BUG_ON(!recv_ioctx);

	ib_dma_sync_single_for_cpu(ch->sport->sdev->device,
				   recv_ioctx->ioctx.dma, srp_max_req_size,
				   DMA_FROM_DEVICE);

	ch_state = srpt_get_ch_state(ch);
	if (unlikely(ch_state == CH_CONNECTING)) {
		list_add_tail(&recv_ioctx->wait_list, &ch->cmd_wait_list);
		goto out;
	}

	if (unlikely(ch_state != CH_LIVE))
		goto out;

	srp_cmd = recv_ioctx->ioctx.buf;
	if (srp_cmd->opcode == SRP_CMD || srp_cmd->opcode == SRP_TSK_MGMT) {
		if (!send_ioctx)
			send_ioctx = srpt_get_send_ioctx(ch);
		if (unlikely(!send_ioctx)) {
			list_add_tail(&recv_ioctx->wait_list,
				      &ch->cmd_wait_list);
			goto out;
		}
	}

	switch (srp_cmd->opcode) {
	case SRP_CMD:
		srpt_handle_cmd(ch, recv_ioctx, send_ioctx);
		break;
	case SRP_TSK_MGMT:
		srpt_handle_tsk_mgmt(ch, recv_ioctx, send_ioctx);
		break;
	case SRP_I_LOGOUT:
		pr_err("Not yet implemented: SRP_I_LOGOUT\n");
		break;
	case SRP_CRED_RSP:
		pr_debug("received SRP_CRED_RSP\n");
		break;
	case SRP_AER_RSP:
		pr_debug("received SRP_AER_RSP\n");
		break;
	case SRP_RSP:
		pr_err("Received SRP_RSP\n");
		break;
	default:
		pr_err("received IU with unknown opcode 0x%x\n",
		       srp_cmd->opcode);
		break;
	}

	srpt_post_recv(ch->sport->sdev, recv_ioctx);
out:
	return;
}
