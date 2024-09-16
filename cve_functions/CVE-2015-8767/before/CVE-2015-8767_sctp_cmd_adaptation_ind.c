static void sctp_cmd_adaptation_ind(sctp_cmd_seq_t *commands,
				    struct sctp_association *asoc)
{
	struct sctp_ulpevent *ev;

	ev = sctp_ulpevent_make_adaptation_indication(asoc, GFP_ATOMIC);

	if (ev)
		sctp_ulpq_tail_event(&asoc->ulpq, ev);
}
