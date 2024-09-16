destroy_addr_opts_fifo(
	addr_opts_fifo *	fifo
	)
{
	addr_opts_node *	aon;

	if (fifo != NULL) {
		do {
			UNLINK_FIFO(aon, *fifo, link);
			if (aon != NULL) {
				destroy_address_node(aon->addr);
				destroy_attr_val_fifo(aon->options);
				free(aon);
			}
		} while (aon != NULL);
		free(fifo);
	}
}
