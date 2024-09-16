bool sk_capable(const struct sock *sk, int cap)
{
	return sk_ns_capable(sk, &init_user_ns, cap);
}
