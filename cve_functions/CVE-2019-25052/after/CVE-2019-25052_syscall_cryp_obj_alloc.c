TEE_Result syscall_cryp_obj_alloc(unsigned long obj_type,
			unsigned long max_key_size, uint32_t *obj)
{
	TEE_Result res;
	struct tee_ta_session *sess;
	struct tee_obj *o;

	if (obj_type == TEE_TYPE_DATA)
		return TEE_ERROR_NOT_SUPPORTED;

	res = tee_ta_get_current_session(&sess);
	if (res != TEE_SUCCESS)
		return res;

	o = tee_obj_alloc();
	if (!o)
		return TEE_ERROR_OUT_OF_MEMORY;

	res = tee_obj_set_type(o, obj_type, max_key_size);
	if (res != TEE_SUCCESS) {
		tee_obj_free(o);
		return res;
	}

	tee_obj_add(to_user_ta_ctx(sess->ctx), o);

	res = tee_svc_copy_kaddr_to_uref(obj, o);
	if (res != TEE_SUCCESS)
		tee_obj_close(to_user_ta_ctx(sess->ctx), o);
	return res;
}
