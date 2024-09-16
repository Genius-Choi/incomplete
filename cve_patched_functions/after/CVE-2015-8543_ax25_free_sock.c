static void ax25_free_sock(struct sock *sk)
{
	ax25_cb_put(sk_to_ax25(sk));
}
