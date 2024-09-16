free_smtp_all(smtp_t * smtp)
{
	FREE(smtp->buffer);
	FREE(smtp->subject);
	FREE(smtp->body);
	FREE(smtp->email_to);
	FREE(smtp);
}
