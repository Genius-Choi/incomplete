static void sctp_generate_t1_cookie_event(unsigned long data)
{
	struct sctp_association *asoc = (struct sctp_association *) data;
	sctp_generate_timeout_event(asoc, SCTP_EVENT_TIMEOUT_T1_COOKIE);
}
