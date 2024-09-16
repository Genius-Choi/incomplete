int hsr_register_frame_out(struct hsr_port *port, struct hsr_node *node,
			   u16 sequence_nr)
{
	if (seq_nr_before_or_eq(sequence_nr, node->seq_out[port->type]))
		return 1;

	node->seq_out[port->type] = sequence_nr;
	return 0;
}
