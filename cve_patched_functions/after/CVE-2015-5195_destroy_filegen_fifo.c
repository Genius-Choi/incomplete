destroy_filegen_fifo(
	filegen_fifo *	fifo
	)
{
	filegen_node *	fg;

	if (fifo != NULL) {
		do {
			UNLINK_FIFO(fg, *fifo, link);
			if (fg != NULL) {
				destroy_attr_val_fifo(fg->options);
				free(fg);
			}
		} while (fg != NULL);
		free(fifo);
	}
}
