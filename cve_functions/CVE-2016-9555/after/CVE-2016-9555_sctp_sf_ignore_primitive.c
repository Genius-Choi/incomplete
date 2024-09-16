sctp_disposition_t sctp_sf_ignore_primitive(
	struct net *net,
	const struct sctp_endpoint *ep,
	const struct sctp_association *asoc,
	const sctp_subtype_t type,
	void *arg,
	sctp_cmd_seq_t *commands)
{
	pr_debug("%s: primitive type:%d is ignored\n", __func__,
		 type.primitive);

	return SCTP_DISPOSITION_DISCARD;
}
