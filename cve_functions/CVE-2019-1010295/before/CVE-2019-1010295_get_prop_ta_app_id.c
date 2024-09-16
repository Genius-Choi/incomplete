static TEE_Result get_prop_ta_app_id(struct tee_ta_session *sess,
				     void *buf, size_t *blen)
{
	if (*blen < sizeof(TEE_UUID)) {
		*blen = sizeof(TEE_UUID);
		return TEE_ERROR_SHORT_BUFFER;
	}
	*blen = sizeof(TEE_UUID);
	return tee_svc_copy_to_user(buf, &sess->ctx->uuid, sizeof(TEE_UUID));
}
