vrrp_dispatcher_release(vrrp_data_t *data)
{
	free_list(&data->vrrp_socket_pool);
#ifdef _WITH_BFD_
	thread_cancel(bfd_thread);
	bfd_thread = NULL;
#endif
}
