static void vhost_scsi_complete_cmd_work(struct vhost_work *work)
{
	struct vhost_scsi *vs = container_of(work, struct vhost_scsi,
					vs_completion_work);
	DECLARE_BITMAP(signal, VHOST_SCSI_MAX_VQ);
	struct virtio_scsi_cmd_resp v_rsp;
	struct vhost_scsi_cmd *cmd;
	struct llist_node *llnode;
	struct se_cmd *se_cmd;
	struct iov_iter iov_iter;
	int ret, vq;

	bitmap_zero(signal, VHOST_SCSI_MAX_VQ);
	llnode = llist_del_all(&vs->vs_completion_list);
	while (llnode) {
		cmd = llist_entry(llnode, struct vhost_scsi_cmd,
				     tvc_completion_list);
		llnode = llist_next(llnode);
		se_cmd = &cmd->tvc_se_cmd;

		pr_debug("%s tv_cmd %p resid %u status %#02x\n", __func__,
			cmd, se_cmd->residual_count, se_cmd->scsi_status);

		memset(&v_rsp, 0, sizeof(v_rsp));
		v_rsp.resid = cpu_to_vhost32(cmd->tvc_vq, se_cmd->residual_count);
		/* TODO is status_qualifier field needed? */
		v_rsp.status = se_cmd->scsi_status;
		v_rsp.sense_len = cpu_to_vhost32(cmd->tvc_vq,
						 se_cmd->scsi_sense_length);
		memcpy(v_rsp.sense, cmd->tvc_sense_buf,
		       se_cmd->scsi_sense_length);

		iov_iter_init(&iov_iter, READ, cmd->tvc_resp_iov,
			      cmd->tvc_in_iovs, sizeof(v_rsp));
		ret = copy_to_iter(&v_rsp, sizeof(v_rsp), &iov_iter);
		if (likely(ret == sizeof(v_rsp))) {
			struct vhost_scsi_virtqueue *q;
			vhost_add_used(cmd->tvc_vq, cmd->tvc_vq_desc, 0);
			q = container_of(cmd->tvc_vq, struct vhost_scsi_virtqueue, vq);
			vq = q - vs->vqs;
			__set_bit(vq, signal);
		} else
			pr_err("Faulted on virtio_scsi_cmd_resp\n");

		vhost_scsi_free_cmd(cmd);
	}

	vq = -1;
	while ((vq = find_next_bit(signal, VHOST_SCSI_MAX_VQ, vq + 1))
		< VHOST_SCSI_MAX_VQ)
		vhost_signal(&vs->dev, &vs->vqs[vq].vq);
}
