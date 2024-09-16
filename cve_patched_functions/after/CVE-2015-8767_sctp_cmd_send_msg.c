static int sctp_cmd_send_msg(struct sctp_association *asoc,
				struct sctp_datamsg *msg)
{
	struct sctp_chunk *chunk;
	int error = 0;

	list_for_each_entry(chunk, &msg->chunks, frag_list) {
		error = sctp_outq_tail(&asoc->outqueue, chunk);
		if (error)
			break;
	}

	return error;
}
