TEE_Result syscall_wait(unsigned long timeout)
{
	TEE_Result res = TEE_SUCCESS;
	uint32_t mytime = 0;
	struct tee_ta_session *s;
	TEE_Time base_time;
	TEE_Time current_time;

	res = tee_ta_get_current_session(&s);
	if (res != TEE_SUCCESS)
		return res;

	res = tee_time_get_sys_time(&base_time);
	if (res != TEE_SUCCESS)
		return res;

	while (true) {
		res = tee_time_get_sys_time(&current_time);
		if (res != TEE_SUCCESS)
			return res;

		if (tee_ta_session_is_cancelled(s, &current_time))
			return TEE_ERROR_CANCEL;

		mytime = (current_time.seconds - base_time.seconds) * 1000 +
		    (int)current_time.millis - (int)base_time.millis;
		if (mytime >= timeout)
			return TEE_SUCCESS;

		tee_time_wait(timeout - mytime);
	}

	return res;
}
