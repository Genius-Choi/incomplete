static int dn_confirm_accept(struct sock *sk, long *timeo, gfp_t allocation)
{
	struct dn_scp *scp = DN_SK(sk);
	DEFINE_WAIT(wait);
	int err;

	if (scp->state != DN_CR)
		return -EINVAL;

	scp->state = DN_CC;
	scp->segsize_loc = dst_metric_advmss(__sk_dst_get(sk));
	dn_send_conn_conf(sk, allocation);

	prepare_to_wait(sk_sleep(sk), &wait, TASK_INTERRUPTIBLE);
	for(;;) {
		release_sock(sk);
		if (scp->state == DN_CC)
			*timeo = schedule_timeout(*timeo);
		lock_sock(sk);
		err = 0;
		if (scp->state == DN_RUN)
			break;
		err = sock_error(sk);
		if (err)
			break;
		err = sock_intr_errno(*timeo);
		if (signal_pending(current))
			break;
		err = -EAGAIN;
		if (!*timeo)
			break;
		prepare_to_wait(sk_sleep(sk), &wait, TASK_INTERRUPTIBLE);
	}
	finish_wait(sk_sleep(sk), &wait);
	if (err == 0) {
		sk->sk_socket->state = SS_CONNECTED;
	} else if (scp->state != DN_CC) {
		sk->sk_socket->state = SS_UNCONNECTED;
	}
	return err;
}
