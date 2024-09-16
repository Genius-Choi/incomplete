TEE_Result syscall_cryp_state_free(unsigned long state)
{
	TEE_Result res;
	struct tee_cryp_state *cs;
	struct tee_ta_session *sess;

	res = tee_ta_get_current_session(&sess);
	if (res != TEE_SUCCESS)
		return res;

	res = tee_svc_cryp_get_state(sess, tee_svc_uref_to_vaddr(state), &cs);
	if (res != TEE_SUCCESS)
		return res;
	cryp_state_free(to_user_ta_ctx(sess->ctx), cs);
	return TEE_SUCCESS;
}
