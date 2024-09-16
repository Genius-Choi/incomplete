static int rose_loopback_running(void)
{
	return timer_pending(&loopback_timer);
}
