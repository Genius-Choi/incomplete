quit_cmd(thread_t * thread)
{
	smtp_t *smtp = THREAD_ARG(thread);

	if (send(thread->u.fd, SMTP_QUIT_CMD, strlen(SMTP_QUIT_CMD), 0) == -1)
		smtp->stage = ERROR;
	else
		smtp->stage++;
	return 0;
}
