TEE_Result syscall_set_ta_time(const TEE_Time *mytime)
{
	TEE_Result res;
	struct tee_ta_session *s = NULL;
	TEE_Time t;

	res = tee_ta_get_current_session(&s);
	if (res != TEE_SUCCESS)
		return res;

	res = tee_svc_copy_from_user(&t, mytime, sizeof(t));
	if (res != TEE_SUCCESS)
		return res;

	return tee_time_set_ta_time((const void *)&s->ctx->uuid, &t);
}
