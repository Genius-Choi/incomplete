body_code(thread_t * thread, int status)
{
	smtp_t *smtp = THREAD_ARG(thread);

	if (status == 250) {
		log_message(LOG_INFO, "SMTP alert successfully sent.");
		smtp->stage++;
	} else {
		log_message(LOG_INFO, "Error processing DOT cmd on SMTP server %s."
				      " SMTP status code = %d"
				    , FMT_SMTP_HOST()
				    , status);
		smtp->stage = ERROR;
	}

	return 0;
}
