static inline struct l2tp_ip_sock *l2tp_ip_sk(const struct sock *sk)
{
	return (struct l2tp_ip_sock *)sk;
}
