TEE_Result tee_svc_copy_to_user(void *uaddr, const void *kaddr, size_t len)
{
	TEE_Result res;
	struct tee_ta_session *s;

	res = tee_ta_get_current_session(&s);
	if (res != TEE_SUCCESS)
		return res;

	res = tee_mmu_check_access_rights(to_user_ta_ctx(s->ctx),
					TEE_MEMORY_ACCESS_WRITE |
					TEE_MEMORY_ACCESS_ANY_OWNER,
					(uaddr_t)uaddr, len);
	if (res != TEE_SUCCESS)
		return res;

	memcpy(uaddr, kaddr, len);
	return TEE_SUCCESS;
}
