destroy_restrict_fifo(
	restrict_fifo *	fifo
	)
{
	restrict_node *	rn;

	if (fifo != NULL) {
		do {
			UNLINK_FIFO(rn, *fifo, link);
			if (rn != NULL)
				destroy_restrict_node(rn);
		} while (rn != NULL);
		free(fifo);
	}
}
