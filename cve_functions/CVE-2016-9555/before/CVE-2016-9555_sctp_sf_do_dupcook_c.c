static sctp_disposition_t sctp_sf_do_dupcook_c(struct net *net,
					const struct sctp_endpoint *ep,
					const struct sctp_association *asoc,
					struct sctp_chunk *chunk,
					sctp_cmd_seq_t *commands,
					struct sctp_association *new_asoc)
{
	/* The cookie should be silently discarded.
	 * The endpoint SHOULD NOT change states and should leave
	 * any timers running.
	 */
	return SCTP_DISPOSITION_DISCARD;
}
