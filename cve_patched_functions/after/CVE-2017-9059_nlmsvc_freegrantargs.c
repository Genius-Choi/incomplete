static void nlmsvc_freegrantargs(struct nlm_rqst *call)
{
	if (call->a_args.lock.oh.data != call->a_owner)
		kfree(call->a_args.lock.oh.data);

	locks_release_private(&call->a_args.lock.fl);
}
