connection_error(thread_t * thread)
{
	smtp_t *smtp = THREAD_ARG(thread);

	log_message(LOG_INFO, "SMTP connection ERROR to %s."
			    , FMT_SMTP_HOST());
	free_smtp_all(smtp);
	return 0;
}
