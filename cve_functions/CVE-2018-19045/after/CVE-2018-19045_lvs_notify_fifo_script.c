lvs_notify_fifo_script(vector_t *strvec)
{
	notify_fifo_script(strvec, "lvs_", &global_data->lvs_notify_fifo);
}
