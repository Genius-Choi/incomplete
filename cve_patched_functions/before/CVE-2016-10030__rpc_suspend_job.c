_rpc_suspend_job(slurm_msg_t *msg)
{
	int time_slice = -1;
	suspend_int_msg_t *req = msg->data;
	uid_t req_uid = g_slurm_auth_get_uid(msg->auth_cred,
					     conf->auth_info);
	List steps;
	ListIterator i;
	step_loc_t *stepd;
	int step_cnt  = 0;
	int rc = SLURM_SUCCESS;
	DEF_TIMERS;

	if (time_slice == -1)
		time_slice = slurm_get_time_slice();
	if ((req->op != SUSPEND_JOB) && (req->op != RESUME_JOB)) {
		error("REQUEST_SUSPEND_INT: bad op code %u", req->op);
		rc = ESLURM_NOT_SUPPORTED;
	}

	/*
	 * check that requesting user ID is the SLURM UID or root
	 */
	if (!_slurm_authorized_user(req_uid)) {
		error("Security violation: suspend_job(%u) from uid %d",
		      req->job_id, req_uid);
		rc =  ESLURM_USER_ID_MISSING;
	}

	/* send a response now, which will include any errors
	 * detected with the request */
	if (msg->conn_fd >= 0) {
		slurm_send_rc_msg(msg, rc);
		if (slurm_close(msg->conn_fd) < 0)
			error("_rpc_suspend_job: close(%d): %m",
			      msg->conn_fd);
		msg->conn_fd = -1;
	}
	if (rc != SLURM_SUCCESS)
		return;

	/* now we can focus on performing the requested action,
	 * which could take a few seconds to complete */
	debug("_rpc_suspend_job jobid=%u uid=%d action=%s", req->job_id,
	      req_uid, req->op == SUSPEND_JOB ? "suspend" : "resume");

	/* Try to get a thread lock for this job. If the lock
	 * is not available then sleep and try again */
	while (!_get_suspend_job_lock(req->job_id)) {
		debug3("suspend lock sleep for %u", req->job_id);
		usleep(10000);
	}
	START_TIMER;

	/* Defer suspend until job prolog and launch complete */
	if (req->op == SUSPEND_JOB)
		_launch_complete_wait(req->job_id);

	if ((req->op == SUSPEND_JOB) && (req->indf_susp))
		switch_g_job_suspend(req->switch_info, 5);

	/* Release or reclaim resources bound to these tasks (task affinity) */
	if (req->op == SUSPEND_JOB) {
		(void) task_g_slurmd_suspend_job(req->job_id);
	} else {
		(void) task_g_slurmd_resume_job(req->job_id);
	}

	/*
	 * Loop through all job steps and call stepd_suspend or stepd_resume
	 * as appropriate. Since the "suspend" action may contains a sleep
	 * (if the launch is in progress) suspend multiple jobsteps in parallel.
	 */
	steps = stepd_available(conf->spooldir, conf->node_name);
	i = list_iterator_create(steps);

	while (1) {
		int x, fdi, fd[NUM_PARALLEL_SUSP_STEPS];
		uint16_t protocol_version[NUM_PARALLEL_SUSP_STEPS];

		fdi = 0;
		while ((stepd = list_next(i))) {
			if (stepd->jobid != req->job_id) {
				/* multiple jobs expected on shared nodes */
				debug3("Step from other job: jobid=%u "
				       "(this jobid=%u)",
				       stepd->jobid, req->job_id);
				continue;
			}
			step_cnt++;

			fd[fdi] = stepd_connect(stepd->directory,
						stepd->nodename, stepd->jobid,
						stepd->stepid,
						&protocol_version[fdi]);
			if (fd[fdi] == -1) {
				debug3("Unable to connect to step %u.%u",
				       stepd->jobid, stepd->stepid);
				continue;
			}

			fdi++;
			if (fdi >= NUM_PARALLEL_SUSP_STEPS)
				break;
		}
		/* check for open connections */
		if (fdi == 0)
			break;

		if (req->op == SUSPEND_JOB) {
			int susp_fail_count = 0;
			/* The suspend RPCs are processed in parallel for
			 * every step in the job */
			for (x = 0; x < fdi; x++) {
				(void) stepd_suspend(fd[x],
						     protocol_version[x],
						     req, 0);
			}
			for (x = 0; x < fdi; x++) {
				if (stepd_suspend(fd[x],
						  protocol_version[x],
						  req, 1) < 0) {
					susp_fail_count++;
				} else {
					close(fd[x]);
					fd[x] = -1;
				}
			}
			/* Suspend RPCs can fail at step startup, so retry */
			if (susp_fail_count) {
				sleep(1);
				for (x = 0; x < fdi; x++) {
					if (fd[x] == -1)
						continue;
					(void) stepd_suspend(
						fd[x],
						protocol_version[x],
						req, 0);
					if (stepd_suspend(
						    fd[x],
						    protocol_version[x],
						    req, 1) >= 0)
						continue;
					debug("Suspend of job %u failed: %m",
					      req->job_id);
				}
			}
		} else {
			/* The resume RPCs are processed in parallel for
			 * every step in the job */
			for (x = 0; x < fdi; x++) {
				(void) stepd_resume(fd[x],
						    protocol_version[x],
						    req, 0);
			}
			for (x = 0; x < fdi; x++) {
				if (stepd_resume(fd[x],
						 protocol_version[x],
						 req, 1) < 0) {
					debug("Resume of job %u failed: %m",
					      req->job_id);
				}
			}
		}
		for (x = 0; x < fdi; x++) {
			/* fd may have been closed by stepd_suspend */
			if (fd[x] != -1)
				close(fd[x]);
		}

		/* check for no more jobs */
		if (fdi < NUM_PARALLEL_SUSP_STEPS)
			break;
	}
	list_iterator_destroy(i);
	FREE_NULL_LIST(steps);

	if ((req->op == RESUME_JOB) && (req->indf_susp))
		switch_g_job_resume(req->switch_info, 5);

	_unlock_suspend_job(req->job_id);

	END_TIMER;
	if (DELTA_TIMER >= (time_slice * 1000000)) {
		if (req->op == SUSPEND_JOB) {
			info("Suspend time for job_id %u was %s. "
			     "Configure SchedulerTimeSlice higher.",
			     req->job_id, TIME_STR);
		} else {
			info("Resume time for job_id %u was %s. "
			     "Configure SchedulerTimeSlice higher.",
			     req->job_id, TIME_STR);
		}
	}

	if (step_cnt == 0) {
		debug2("No steps in jobid %u to suspend/resume", req->job_id);
	}
}
