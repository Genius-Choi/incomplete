TEE_Result syscall_get_time(unsigned long cat, TEE_Time *mytime)
{
	TEE_Result res, res2;
	struct tee_ta_session *s = NULL;
	TEE_Time t;

	res = tee_ta_get_current_session(&s);
	if (res != TEE_SUCCESS)
		return res;

	switch (cat) {
	case UTEE_TIME_CAT_SYSTEM:
		res = tee_time_get_sys_time(&t);
		break;
	case UTEE_TIME_CAT_TA_PERSISTENT:
		res = tee_time_get_ta_time((const void *)&s->ctx->uuid, &t);
		break;
	case UTEE_TIME_CAT_REE:
		res = tee_time_get_ree_time(&t);
		break;
	default:
		res = TEE_ERROR_BAD_PARAMETERS;
		break;
	}

	if (res == TEE_SUCCESS || res == TEE_ERROR_OVERFLOW) {
		res2 = tee_svc_copy_to_user(mytime, &t, sizeof(t));
		if (res2 != TEE_SUCCESS)
			res = res2;
	}

	return res;
}
