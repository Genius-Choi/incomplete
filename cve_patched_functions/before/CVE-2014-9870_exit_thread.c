void exit_thread(void)
{
	thread_notify(THREAD_NOTIFY_EXIT, current_thread_info());
}
