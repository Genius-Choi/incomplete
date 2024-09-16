static int nlmclnt_cancel(struct nlm_host *host, int block, struct file_lock *fl)
{
	struct nlm_rqst	*req;
	int status;

	dprintk("lockd: blocking lock attempt was interrupted by a signal.\n"
		"       Attempting to cancel lock.\n");

	req = nlm_alloc_call(nlm_get_host(host));
	if (!req)
		return -ENOMEM;
	req->a_flags = RPC_TASK_ASYNC;

	nlmclnt_setlockargs(req, fl);
	req->a_args.block = block;

	atomic_inc(&req->a_count);
	status = nlmclnt_async_call(nfs_file_cred(fl->fl_file), req,
			NLMPROC_CANCEL, &nlmclnt_cancel_ops);
	if (status == 0 && req->a_res.status == nlm_lck_denied)
		status = -ENOLCK;
	nlmclnt_release_call(req);
	return status;
}
