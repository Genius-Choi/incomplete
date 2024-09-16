struct sock *vsock_find_bound_socket(struct sockaddr_vm *addr)
{
	struct sock *sk;

	spin_lock_bh(&vsock_table_lock);
	sk = __vsock_find_bound_socket(addr);
	if (sk)
		sock_hold(sk);

	spin_unlock_bh(&vsock_table_lock);

	return sk;
}
