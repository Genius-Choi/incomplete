TEE_Result syscall_cryp_random_number_generate(void *buf, size_t blen)
{
	TEE_Result res;
	struct tee_ta_session *sess;

	res = tee_ta_get_current_session(&sess);
	if (res != TEE_SUCCESS)
		return res;

	res = tee_mmu_check_access_rights(to_user_ta_ctx(sess->ctx),
					  TEE_MEMORY_ACCESS_WRITE |
					  TEE_MEMORY_ACCESS_ANY_OWNER,
					  (uaddr_t)buf, blen);
	if (res != TEE_SUCCESS)
		return res;

	res = crypto_rng_read(buf, blen);
	if (res != TEE_SUCCESS)
		return res;

	return res;
}
