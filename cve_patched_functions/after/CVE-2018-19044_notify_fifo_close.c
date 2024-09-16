notify_fifo_close(notify_fifo_t* global_fifo, notify_fifo_t* fifo)
{
	if (global_fifo->fd != -1)
		fifo_close(global_fifo);

	fifo_close(fifo);
}
