global_notify_fifo(vector_t *strvec)
{
	notify_fifo(strvec, "", &global_data->notify_fifo);
}
