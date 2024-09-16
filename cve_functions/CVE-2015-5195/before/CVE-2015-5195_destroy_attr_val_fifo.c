destroy_attr_val_fifo(
	attr_val_fifo *	av_fifo
	)
{
	attr_val *	av;

	if (av_fifo != NULL) {
		do {
			UNLINK_FIFO(av, *av_fifo, link);
			if (av != NULL) {
				if (T_String == av->type)
					free(av->value.s);
				free(av);
			}
		} while (av != NULL);
		free(av_fifo);
	}
}
