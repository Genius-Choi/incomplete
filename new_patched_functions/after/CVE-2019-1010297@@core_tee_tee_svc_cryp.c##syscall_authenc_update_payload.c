TEE_Result syscall_authenc_update_payload(unsigned long state,
			const void *src_data, size_t src_len, void *dst_data,
			uint64_t *dst_len)
{
	TEE_Result res;
	struct tee_cryp_state *cs;
	struct tee_ta_session *sess;
	uint64_t dlen;
	size_t tmp_dlen;

	res = tee_ta_get_current_session(&sess);
	if (res != TEE_SUCCESS)
		return res;

	res = tee_svc_cryp_get_state(sess, tee_svc_uref_to_vaddr(state), &cs);
	if (res != TEE_SUCCESS)
		return res;

	res = tee_mmu_check_access_rights(to_user_ta_ctx(sess->ctx),
					  TEE_MEMORY_ACCESS_READ |
					  TEE_MEMORY_ACCESS_ANY_OWNER,
					  (uaddr_t) src_data, src_len);
	if (res != TEE_SUCCESS)
		return res;

	res = tee_svc_copy_from_user(&dlen, dst_len, sizeof(dlen));
	if (res != TEE_SUCCESS)
		return res;

	res = tee_mmu_check_access_rights(to_user_ta_ctx(sess->ctx),
					  TEE_MEMORY_ACCESS_READ |
					  TEE_MEMORY_ACCESS_WRITE |
					  TEE_MEMORY_ACCESS_ANY_OWNER,
					  (uaddr_t)dst_data, dlen);
	if (res != TEE_SUCCESS)
		return res;

	if (dlen < src_len) {
		res = TEE_ERROR_SHORT_BUFFER;
		goto out;
	}

	tmp_dlen = dlen;
	res = crypto_authenc_update_payload(cs->ctx, cs->algo, cs->mode,
					    src_data, src_len, dst_data,
					    &tmp_dlen);
	dlen = tmp_dlen;

out:
	if (res == TEE_SUCCESS || res == TEE_ERROR_SHORT_BUFFER) {
		TEE_Result res2 = tee_svc_copy_to_user(dst_len, &dlen,
						       sizeof(*dst_len));
		if (res2 != TEE_SUCCESS)
			res = res2;
	}

	return res;
}
