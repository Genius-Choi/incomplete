rcpt_code(thread_t * thread, int status)
{
	smtp_t *smtp = THREAD_ARG(thread);
	char *fetched_email;

	if (status == 250) {
		smtp->email_it++;

		fetched_email = fetch_next_email(smtp);

		if (!fetched_email)
			smtp->stage++;
	} else {
		log_message(LOG_INFO, "Error processing RCPT cmd on SMTP server %s."
				      " SMTP status code = %d"
				    , FMT_SMTP_HOST()
				    , status);
		smtp->stage = ERROR;
	}

	return 0;
}
