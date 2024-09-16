lvs_notify_fifo(vector_t *strvec)
{
	notify_fifo(strvec, "lvs_", &global_data->lvs_notify_fifo);
}
