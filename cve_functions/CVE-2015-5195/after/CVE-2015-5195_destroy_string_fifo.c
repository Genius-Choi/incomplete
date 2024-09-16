destroy_string_fifo(
	string_fifo *	fifo
	)
{
	string_node *	sn;

	if (fifo != NULL) {
		do {
			UNLINK_FIFO(sn, *fifo, link);
			if (sn != NULL) {
				if (sn->s != NULL)
					free(sn->s);
				free(sn);
			}
		} while (sn != NULL);
		free(fifo);
	}
}
