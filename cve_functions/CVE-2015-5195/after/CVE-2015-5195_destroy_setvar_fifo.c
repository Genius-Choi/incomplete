destroy_setvar_fifo(
	setvar_fifo *	fifo
	)
{
	setvar_node *	sv;

	if (fifo != NULL) {
		do {
			UNLINK_FIFO(sv, *fifo, link);
			if (sv != NULL) {
				free(sv->var);
				free(sv->val);
				free(sv);
			}
		} while (sv != NULL);
		free(fifo);
	}
}
