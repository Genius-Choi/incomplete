int perf_unregister_guest_info_callbacks(struct perf_guest_info_callbacks *cbs)
{
	perf_guest_cbs = NULL;
	return 0;
}
