static struct sock *__vsock_find_bound_socket(struct sockaddr_vm *addr)
{
	struct vsock_sock *vsk;

	list_for_each_entry(vsk, vsock_bound_sockets(addr), bound_table)
		if (addr->svm_port == vsk->local_addr.svm_port)
			return sk_vsock(vsk);

	return NULL;
}
