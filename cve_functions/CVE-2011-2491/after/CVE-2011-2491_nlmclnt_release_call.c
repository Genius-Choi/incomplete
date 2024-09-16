void nlmclnt_release_call(struct nlm_rqst *call)
{
	if (!atomic_dec_and_test(&call->a_count))
		return;
	nlmclnt_release_host(call->a_host);
	nlmclnt_release_lockargs(call);
	kfree(call);
}
