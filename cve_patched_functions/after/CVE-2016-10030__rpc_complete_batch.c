_rpc_complete_batch(slurm_msg_t *msg)
{
	int		i, rc, msg_rc;
	slurm_msg_t	resp_msg;
	uid_t           uid    = g_slurm_auth_get_uid(msg->auth_cred,
						      conf->auth_info);
	complete_batch_script_msg_t *req = msg->data;
	static int	running_serial = -1;
	uint16_t msg_type;

	if (running_serial == -1) {
		char *select_type = slurm_get_select_type();
		if (!xstrcmp(select_type, "select/serial"))
			running_serial = 1;
		else
			running_serial = 0;
		xfree(select_type);
	}

	if (!_slurm_authorized_user(uid)) {
		error("Security violation: complete_batch(%u) from uid %d",
		      req->job_id, uid);
		if (msg->conn_fd >= 0)
			slurm_send_rc_msg(msg, ESLURM_USER_ID_MISSING);
		return;
	}

	slurm_send_rc_msg(msg, SLURM_SUCCESS);

	if (running_serial) {
		_rpc_terminate_batch_job(
			req->job_id, req->user_id, req->node_name);
		msg_type = REQUEST_COMPLETE_BATCH_JOB;
	} else
		msg_type = msg->msg_type;

	for (i = 0; i <= MAX_RETRY; i++) {
		if (conf->msg_aggr_window_msgs > 1) {
			slurm_msg_t *req_msg =
				xmalloc_nz(sizeof(slurm_msg_t));
			slurm_msg_t_init(req_msg);
			req_msg->msg_type = msg_type;
			req_msg->data = msg->data;
			msg->data = NULL;

			msg_aggr_add_msg(req_msg, 1,
					 _handle_old_batch_job_launch);
			return;
		} else {
			slurm_msg_t req_msg;
			slurm_msg_t_init(&req_msg);
			req_msg.msg_type = msg_type;
			req_msg.data	 = msg->data;
			msg_rc = slurm_send_recv_controller_msg(
				&req_msg, &resp_msg);

			if (msg_rc == SLURM_SUCCESS)
				break;
		}
		info("Retrying job complete RPC for job %u", req->job_id);
		sleep(RETRY_DELAY);
	}
	if (i > MAX_RETRY) {
		error("Unable to send job complete message: %m");
		return;
	}

	if (resp_msg.msg_type == RESPONSE_SLURM_RC) {
		last_slurmctld_msg = time(NULL);
		rc = ((return_code_msg_t *) resp_msg.data)->return_code;
		slurm_free_return_code_msg(resp_msg.data);
		if (rc) {
			error("complete_batch for job %u: %s", req->job_id,
			      slurm_strerror(rc));
		}
		return;
	}

	_handle_old_batch_job_launch(&resp_msg);
}
