int sctp_has_association(const union sctp_addr *laddr,
			 const union sctp_addr *paddr)
{
	struct sctp_association *asoc;
	struct sctp_transport *transport;

	if ((asoc = sctp_lookup_association(laddr, paddr, &transport))) {
		sctp_association_put(asoc);
		return 1;
	}

	return 0;
}
