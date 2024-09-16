TEE_Result syscall_open_ta_session(const TEE_UUID *dest,
			unsigned long cancel_req_to,
			struct utee_params *usr_param, uint32_t *ta_sess,
			uint32_t *ret_orig)
{
	TEE_Result res;
	uint32_t ret_o = TEE_ORIGIN_TEE;
	struct tee_ta_session *s = NULL;
	struct tee_ta_session *sess;
	struct mobj *mobj_param = NULL;
	TEE_UUID *uuid = malloc(sizeof(TEE_UUID));
	struct tee_ta_param *param = malloc(sizeof(struct tee_ta_param));
	TEE_Identity *clnt_id = malloc(sizeof(TEE_Identity));
	void *tmp_buf_va[TEE_NUM_PARAMS] = { NULL };
	struct user_ta_ctx *utc;

	if (uuid == NULL || param == NULL || clnt_id == NULL) {
		res = TEE_ERROR_OUT_OF_MEMORY;
		goto out_free_only;
	}

	memset(param, 0, sizeof(struct tee_ta_param));

	res = tee_ta_get_current_session(&sess);
	if (res != TEE_SUCCESS)
		goto out_free_only;
	utc = to_user_ta_ctx(sess->ctx);

	res = tee_svc_copy_from_user(uuid, dest, sizeof(TEE_UUID));
	if (res != TEE_SUCCESS)
		goto function_exit;

	clnt_id->login = TEE_LOGIN_TRUSTED_APP;
	memcpy(&clnt_id->uuid, &sess->ctx->uuid, sizeof(TEE_UUID));

	res = tee_svc_copy_param(sess, NULL, usr_param, param, tmp_buf_va,
				 &mobj_param);
	if (res != TEE_SUCCESS)
		goto function_exit;

	res = tee_ta_open_session(&ret_o, &s, &utc->open_sessions, uuid,
				  clnt_id, cancel_req_to, param);
	tee_mmu_set_ctx(&utc->ctx);
	if (res != TEE_SUCCESS)
		goto function_exit;

	res = tee_svc_update_out_param(param, tmp_buf_va, usr_param);

function_exit:
	mobj_free(mobj_param);
	if (res == TEE_SUCCESS)
		tee_svc_copy_kaddr_to_uref(ta_sess, s);
	tee_svc_copy_to_user(ret_orig, &ret_o, sizeof(ret_o));

out_free_only:
	free(param);
	free(uuid);
	free(clnt_id);
	return res;
}
