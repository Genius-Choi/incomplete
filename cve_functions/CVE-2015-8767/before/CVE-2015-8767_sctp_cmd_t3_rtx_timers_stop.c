static void sctp_cmd_t3_rtx_timers_stop(sctp_cmd_seq_t *cmds,
					struct sctp_association *asoc)
{
	struct sctp_transport *t;

	list_for_each_entry(t, &asoc->peer.transport_addr_list,
			transports) {
		if (del_timer(&t->T3_rtx_timer))
			sctp_transport_put(t);
	}
}
