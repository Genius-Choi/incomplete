struct sctp_chunk *sctp_make_violation_max_retrans(
	const struct sctp_association *asoc,
	const struct sctp_chunk *chunk)
{
	struct sctp_chunk *retval;
	static const char error[] = "Association exceeded its max_retans count";
	size_t payload_len = sizeof(error) + sizeof(sctp_errhdr_t);

	retval = sctp_make_abort(asoc, chunk, payload_len);
	if (!retval)
		goto nodata;

	sctp_init_cause(retval, SCTP_ERROR_PROTO_VIOLATION, sizeof(error));
	sctp_addto_chunk(retval, sizeof(error), error);

nodata:
	return retval;
}
