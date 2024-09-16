static TEE_Result get_prop_tee_sys_time_prot_level(
			struct tee_ta_session *sess __unused,
			void *buf, size_t *blen)
{
	uint32_t prot;

	if (*blen < sizeof(prot)) {
		*blen = sizeof(prot);
		return TEE_ERROR_SHORT_BUFFER;
	}
	*blen = sizeof(prot);
	prot = tee_time_get_sys_time_protection_level();
	return tee_svc_copy_to_user(buf, &prot, sizeof(prot));
}
