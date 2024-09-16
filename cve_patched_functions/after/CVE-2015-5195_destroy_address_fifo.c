destroy_address_fifo(
	address_fifo *	pfifo
	)
{
	address_node *	addr_node;

	if (pfifo != NULL) {
		do {
			UNLINK_FIFO(addr_node, *pfifo, link);
			if (addr_node != NULL)
				destroy_address_node(addr_node);
		} while (addr_node != NULL);
		free(pfifo);
	}
}
