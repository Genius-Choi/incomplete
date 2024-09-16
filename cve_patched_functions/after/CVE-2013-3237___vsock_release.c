static void __vsock_release(struct sock *sk)
{
	if (sk) {
		struct sk_buff *skb;
		struct sock *pending;
		struct vsock_sock *vsk;

		vsk = vsock_sk(sk);
		pending = NULL;	/* Compiler warning. */

		if (vsock_in_bound_table(vsk))
			vsock_remove_bound(vsk);

		if (vsock_in_connected_table(vsk))
			vsock_remove_connected(vsk);

		transport->release(vsk);

		lock_sock(sk);
		sock_orphan(sk);
		sk->sk_shutdown = SHUTDOWN_MASK;

		while ((skb = skb_dequeue(&sk->sk_receive_queue)))
			kfree_skb(skb);

		/* Clean up any sockets that never were accepted. */
		while ((pending = vsock_dequeue_accept(sk)) != NULL) {
			__vsock_release(pending);
			sock_put(pending);
		}

		release_sock(sk);
		sock_put(sk);
	}
}
