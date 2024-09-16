static TEE_Result get_prop_client_id(struct tee_ta_session *sess __unused,
				     void *buf, size_t *blen)
{
	if (*blen < sizeof(TEE_Identity)) {
		*blen = sizeof(TEE_Identity);
		return TEE_ERROR_SHORT_BUFFER;
	}
	*blen = sizeof(TEE_Identity);
	return tee_svc_copy_to_user(buf, &sess->clnt_id, sizeof(TEE_Identity));
}
