mail_cmd(thread_t * thread)
{
	smtp_t *smtp = THREAD_ARG(thread);
	char *buffer;

	buffer = (char *) MALLOC(SMTP_BUFFER_MAX);
	snprintf(buffer, SMTP_BUFFER_MAX, SMTP_MAIL_CMD, global_data->email_from);
	if (send(thread->u.fd, buffer, strlen(buffer), 0) == -1)
		smtp->stage = ERROR;
	FREE(buffer);

	return 0;
}
