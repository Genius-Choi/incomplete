void ip6_dgram_sock_seq_show(struct seq_file *seq, struct sock *sp,
			     __u16 srcp, __u16 destp, int bucket)
{
	const struct in6_addr *dest, *src;

	dest  = &sp->sk_v6_daddr;
	src   = &sp->sk_v6_rcv_saddr;
	seq_printf(seq,
		   "%5d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X "
		   "%02X %08X:%08X %02X:%08lX %08X %5u %8d %lu %d %pK %d\n",
		   bucket,
		   src->s6_addr32[0], src->s6_addr32[1],
		   src->s6_addr32[2], src->s6_addr32[3], srcp,
		   dest->s6_addr32[0], dest->s6_addr32[1],
		   dest->s6_addr32[2], dest->s6_addr32[3], destp,
		   sp->sk_state,
		   sk_wmem_alloc_get(sp),
		   sk_rmem_alloc_get(sp),
		   0, 0L, 0,
		   from_kuid_munged(seq_user_ns(seq), sock_i_uid(sp)),
		   0,
		   sock_i_ino(sp),
		   atomic_read(&sp->sk_refcnt), sp,
		   atomic_read(&sp->sk_drops));
}
