static void ax25_free_sock(struct sock *sk)
{
	ax25_cb_put(ax25_sk(sk));
}
