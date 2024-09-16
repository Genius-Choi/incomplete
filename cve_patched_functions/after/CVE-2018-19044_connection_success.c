connection_success(thread_t * thread)
{
	smtp_t *smtp = THREAD_ARG(thread);

	log_message(LOG_INFO, "Remote SMTP server %s connected."
			    , FMT_SMTP_HOST());

	smtp->stage = connect_success;
	thread_add_read(thread->master, smtp_read_thread, smtp,
			smtp->fd, global_data->smtp_connection_to);
	return 0;
}
