static void nlmsvc_grant_release(void *data)
{
	struct nlm_rqst		*call = data;
	nlmsvc_release_block(call->a_block);
}
