register_notify_addresses(void)
{
	register_thread_address("child_killed_thread", child_killed_thread);
}
