static void sctp_cmd_setup_t2(sctp_cmd_seq_t *cmds,
			      struct sctp_association *asoc,
			      struct sctp_chunk *chunk)
{
	struct sctp_transport *t;

	if (chunk->transport)
		t = chunk->transport;
	else {
		t = sctp_assoc_choose_alter_transport(asoc,
					      asoc->shutdown_last_sent_to);
		chunk->transport = t;
	}
	asoc->shutdown_last_sent_to = t;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T2_SHUTDOWN] = t->rto;
}
