static void sco_sock_close(struct sock *sk)
{
	lock_sock(sk);
	sco_sock_clear_timer(sk);
	__sco_sock_close(sk);
	release_sock(sk);
}
