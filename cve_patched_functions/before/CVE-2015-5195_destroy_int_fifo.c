destroy_int_fifo(
	int_fifo *	fifo
	)
{
	int_node *	i_n;

	if (fifo != NULL) {
		do {
			UNLINK_FIFO(i_n, *fifo, link);
			if (i_n != NULL)
				free(i_n);
		} while (i_n != NULL);
		free(fifo);
	}
}
