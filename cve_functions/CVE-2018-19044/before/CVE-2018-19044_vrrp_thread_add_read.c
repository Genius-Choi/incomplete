vrrp_thread_add_read(vrrp_t *vrrp)
{
	vrrp->sockets->thread = thread_add_read_sands(master, vrrp_read_dispatcher_thread,
						vrrp->sockets, vrrp->sockets->fd_in, vrrp_compute_timer(vrrp->sockets));
}
