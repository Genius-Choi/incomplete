static void dccp_v6_destroy_sock(struct sock *sk)
{
	dccp_destroy_sock(sk);
	inet6_destroy_sock(sk);
}
