struct dst_entry *__inet6_csk_dst_check(struct sock *sk, u32 cookie)
{
	return __sk_dst_check(sk, cookie);
}
