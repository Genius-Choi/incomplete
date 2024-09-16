static void raw_destroy(struct sock *sk)
{
	lock_sock(sk);
	ip_flush_pending_frames(sk);
	release_sock(sk);
}
