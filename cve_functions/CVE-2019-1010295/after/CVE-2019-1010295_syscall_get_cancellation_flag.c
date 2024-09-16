TEE_Result syscall_get_cancellation_flag(uint32_t *cancel)
{
	TEE_Result res;
	struct tee_ta_session *s = NULL;
	uint32_t c;

	res = tee_ta_get_current_session(&s);
	if (res != TEE_SUCCESS)
		return res;

	c = tee_ta_session_is_cancelled(s, NULL);

	return tee_svc_copy_to_user(cancel, &c, sizeof(c));
}
