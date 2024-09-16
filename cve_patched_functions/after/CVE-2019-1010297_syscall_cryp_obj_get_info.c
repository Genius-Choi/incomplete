TEE_Result syscall_cryp_obj_get_info(unsigned long obj, TEE_ObjectInfo *info)
{
	TEE_Result res;
	struct tee_ta_session *sess;
	struct tee_obj *o;

	res = tee_ta_get_current_session(&sess);
	if (res != TEE_SUCCESS)
		goto exit;

	res = tee_obj_get(to_user_ta_ctx(sess->ctx),
			  tee_svc_uref_to_vaddr(obj), &o);
	if (res != TEE_SUCCESS)
		goto exit;

	res = tee_svc_copy_to_user(info, &o->info, sizeof(o->info));

exit:
	return res;
}
