static void __sk_free(struct sock *sk)
{
	struct sk_filter *filter;

	if (sk->sk_destruct)
		sk->sk_destruct(sk);

	filter = rcu_dereference_check(sk->sk_filter,
				       atomic_read(&sk->sk_wmem_alloc) == 0);
	if (filter) {
		sk_filter_uncharge(sk, filter);
		RCU_INIT_POINTER(sk->sk_filter, NULL);
	}

	sock_disable_timestamp(sk, SK_FLAGS_TIMESTAMP);

	if (atomic_read(&sk->sk_omem_alloc))
		printk(KERN_DEBUG "%s: optmem leakage (%d bytes) detected.\n",
		       __func__, atomic_read(&sk->sk_omem_alloc));

	if (sk->sk_peer_cred)
		put_cred(sk->sk_peer_cred);
	put_pid(sk->sk_peer_pid);
	put_net(sock_net(sk));
	sk_prot_free(sk->sk_prot_creator, sk);
}
