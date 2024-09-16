mail_code(thread_t * thread, int status)
{
	smtp_t *smtp = THREAD_ARG(thread);

	if (status == 250) {
		smtp->stage++;
	} else {
		log_message(LOG_INFO, "Error processing MAIL cmd on SMTP server %s."
				      " SMTP status code = %d"
				    , FMT_SMTP_HOST()
				    , status);
		smtp->stage = ERROR;
	}

	return 0;
}
