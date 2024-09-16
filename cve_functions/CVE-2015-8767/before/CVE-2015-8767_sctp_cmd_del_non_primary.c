static void sctp_cmd_del_non_primary(struct sctp_association *asoc)
{
	struct sctp_transport *t;
	struct list_head *pos;
	struct list_head *temp;

	list_for_each_safe(pos, temp, &asoc->peer.transport_addr_list) {
		t = list_entry(pos, struct sctp_transport, transports);
		if (!sctp_cmp_addr_exact(&t->ipaddr,
					 &asoc->peer.primary_addr)) {
			sctp_assoc_rm_peer(asoc, t);
		}
	}
}
