void __sk_mem_reclaim(struct sock *sk)
{
	sk_memory_allocated_sub(sk,
				sk->sk_forward_alloc >> SK_MEM_QUANTUM_SHIFT);
	sk->sk_forward_alloc &= SK_MEM_QUANTUM - 1;

	if (sk_under_memory_pressure(sk) &&
	    (sk_memory_allocated(sk) < sk_prot_mem_limits(sk, 0)))
		sk_leave_memory_pressure(sk);
}
