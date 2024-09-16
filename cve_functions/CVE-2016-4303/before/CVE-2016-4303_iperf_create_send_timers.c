iperf_create_send_timers(struct iperf_test * test)
{
    struct timeval now;
    struct iperf_stream *sp;
    TimerClientData cd;

    if (gettimeofday(&now, NULL) < 0) {
	i_errno = IEINITTEST;
	return -1;
    }
    SLIST_FOREACH(sp, &test->streams, streams) {
        sp->green_light = 1;
	if (test->settings->rate != 0) {
	    cd.p = sp;
	    sp->send_timer = tmr_create((struct timeval*) 0, send_timer_proc, cd, 100000L, 1);
	    /* (Repeat every tenth second - arbitrary often value.) */
	    if (sp->send_timer == NULL) {
		i_errno = IEINITTEST;
		return -1;
	    }
	}
    }
    return 0;
}
