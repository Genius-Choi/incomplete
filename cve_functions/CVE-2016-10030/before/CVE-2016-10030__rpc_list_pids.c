_rpc_list_pids(slurm_msg_t *msg)
{
	job_step_id_msg_t *req = (job_step_id_msg_t *)msg->data;
	slurm_msg_t        resp_msg;
	job_step_pids_t *resp = NULL;
	int fd;
	uid_t req_uid;
	uid_t job_uid;
	uint16_t protocol_version = 0;

	debug3("Entering _rpc_list_pids");
	/* step completion messages are only allowed from other slurmstepd,
	 * so only root or SlurmUser is allowed here */
	req_uid = g_slurm_auth_get_uid(msg->auth_cred, conf->auth_info);

	job_uid = _get_job_uid(req->job_id);

	if ((int)job_uid < 0) {
		error("stat_pid for invalid job_id: %u",
		      req->job_id);
		if (msg->conn_fd >= 0)
			slurm_send_rc_msg(msg, ESLURM_INVALID_JOB_ID);
		return  ESLURM_INVALID_JOB_ID;
	}

	/*
	 * check that requesting user ID is the SLURM UID or root
	 */
	if ((req_uid != job_uid)
	    && (!_slurm_authorized_user(req_uid))) {
		error("stat_pid from uid %ld for job %u "
		      "owned by uid %ld",
		      (long) req_uid, req->job_id, (long) job_uid);

		if (msg->conn_fd >= 0) {
			slurm_send_rc_msg(msg, ESLURM_USER_ID_MISSING);
			return ESLURM_USER_ID_MISSING;/* or bad in this case */
		}
	}

	resp = xmalloc(sizeof(job_step_pids_t));
	slurm_msg_t_copy(&resp_msg, msg);
	resp->node_name = xstrdup(conf->node_name);
	resp->pid_cnt = 0;
	resp->pid = NULL;
	fd = stepd_connect(conf->spooldir, conf->node_name,
			   req->job_id, req->step_id, &protocol_version);
	if (fd == -1) {
		error("stepd_connect to %u.%u failed: %m",
		      req->job_id, req->step_id);
		slurm_send_rc_msg(msg, ESLURM_INVALID_JOB_ID);
		slurm_free_job_step_pids(resp);
		return  ESLURM_INVALID_JOB_ID;

	}

	if (stepd_list_pids(fd, protocol_version,
			    &resp->pid, &resp->pid_cnt) == SLURM_ERROR) {
		debug("No pids for nonexistent job %u.%u requested",
		      req->job_id, req->step_id);
	}

	close(fd);

	resp_msg.msg_type = RESPONSE_JOB_STEP_PIDS;
	resp_msg.data     = resp;

	slurm_send_node_msg(msg->conn_fd, &resp_msg);
	slurm_free_job_step_pids(resp);
	return SLURM_SUCCESS;
}
