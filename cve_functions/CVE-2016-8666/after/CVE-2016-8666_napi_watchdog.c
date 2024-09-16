static enum hrtimer_restart napi_watchdog(struct hrtimer *timer)
{
	struct napi_struct *napi;

	napi = container_of(timer, struct napi_struct, timer);
	if (napi->gro_list)
		napi_schedule(napi);

	return HRTIMER_NORESTART;
}
