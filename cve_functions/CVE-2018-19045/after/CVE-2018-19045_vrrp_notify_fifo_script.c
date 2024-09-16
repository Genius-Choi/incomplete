vrrp_notify_fifo_script(vector_t *strvec)
{
	notify_fifo_script(strvec, "vrrp_", &global_data->vrrp_notify_fifo);
}
