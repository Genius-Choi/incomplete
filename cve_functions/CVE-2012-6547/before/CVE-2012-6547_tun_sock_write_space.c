static void tun_sock_write_space(struct sock *sk)
{
	struct tun_struct *tun;
	wait_queue_head_t *wqueue;

	if (!sock_writeable(sk))
		return;

	if (!test_and_clear_bit(SOCK_ASYNC_NOSPACE, &sk->sk_socket->flags))
		return;

	wqueue = sk_sleep(sk);
	if (wqueue && waitqueue_active(wqueue))
		wake_up_interruptible_sync_poll(wqueue, POLLOUT |
						POLLWRNORM | POLLWRBAND);

	tun = tun_sk(sk)->tun;
	kill_fasync(&tun->fasync, SIGIO, POLL_OUT);
}
