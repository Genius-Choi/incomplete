vrrp_bfd_thread(thread_t * thread)
{
	bfd_event_t evt;

	bfd_thread = thread_add_read(master, vrrp_bfd_thread, NULL,
				     thread->u.fd, TIMER_NEVER);

	if (thread->type != THREAD_READY_FD)
		return 0;

	while (read(thread->u.fd, &evt, sizeof(bfd_event_t)) != -1)
		vrrp_handle_bfd_event(&evt);

	return 0;
}
