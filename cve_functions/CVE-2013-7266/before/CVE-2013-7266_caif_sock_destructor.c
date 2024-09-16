static void caif_sock_destructor(struct sock *sk)
{
	struct caifsock *cf_sk = container_of(sk, struct caifsock, sk);
	caif_assert(!atomic_read(&sk->sk_wmem_alloc));
	caif_assert(sk_unhashed(sk));
	caif_assert(!sk->sk_socket);
	if (!sock_flag(sk, SOCK_DEAD)) {
		pr_debug("Attempt to release alive CAIF socket: %p\n", sk);
		return;
	}
	sk_stream_kill_queues(&cf_sk->sk);
	caif_free_client(&cf_sk->layer);
}
