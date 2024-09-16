TEE_Result syscall_check_access_rights(unsigned long flags, const void *buf,
				       size_t len)
{
	TEE_Result res;
	struct tee_ta_session *s;

	res = tee_ta_get_current_session(&s);
	if (res != TEE_SUCCESS)
		return res;

	return tee_mmu_check_access_rights(to_user_ta_ctx(s->ctx), flags,
					   (uaddr_t)buf, len);
}
