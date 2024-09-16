vrrp_thread_requeue_read(vrrp_t *vrrp)
{
	thread_requeue_read(master, vrrp->sockets->fd_in, vrrp_compute_timer(vrrp->sockets));
}
