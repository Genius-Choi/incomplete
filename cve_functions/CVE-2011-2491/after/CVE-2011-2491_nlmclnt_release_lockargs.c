static void nlmclnt_release_lockargs(struct nlm_rqst *req)
{
	BUG_ON(req->a_args.lock.fl.fl_ops != NULL);
}
