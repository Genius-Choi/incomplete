static bool vsock_is_pending(struct sock *sk)
{
	struct vsock_sock *vsk = vsock_sk(sk);
	return !list_empty(&vsk->pending_links);
}
