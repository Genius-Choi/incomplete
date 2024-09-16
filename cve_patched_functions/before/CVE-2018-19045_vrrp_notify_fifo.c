vrrp_notify_fifo(vector_t *strvec)
{
	notify_fifo(strvec, "vrrp_", &global_data->vrrp_notify_fifo);
}
