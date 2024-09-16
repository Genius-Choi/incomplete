TEE_Result syscall_unmask_cancellation(uint32_t *old_mask)
{
	TEE_Result res;
	struct tee_ta_session *s = NULL;
	uint32_t m;

	res = tee_ta_get_current_session(&s);
	if (res != TEE_SUCCESS)
		return res;

	m = s->cancel_mask;
	s->cancel_mask = false;
	return tee_svc_copy_to_user(old_mask, &m, sizeof(m));
}
