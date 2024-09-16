static int dn_ioctl(struct socket *sock, unsigned int cmd, unsigned long arg)
{
	struct sock *sk = sock->sk;
	struct dn_scp *scp = DN_SK(sk);
	int err = -EOPNOTSUPP;
	long amount = 0;
	struct sk_buff *skb;
	int val;

	switch(cmd)
	{
	case SIOCGIFADDR:
	case SIOCSIFADDR:
		return dn_dev_ioctl(cmd, (void __user *)arg);

	case SIOCATMARK:
		lock_sock(sk);
		val = !skb_queue_empty(&scp->other_receive_queue);
		if (scp->state != DN_RUN)
			val = -ENOTCONN;
		release_sock(sk);
		return val;

	case TIOCOUTQ:
		amount = sk->sk_sndbuf - sk_wmem_alloc_get(sk);
		if (amount < 0)
			amount = 0;
		err = put_user(amount, (int __user *)arg);
		break;

	case TIOCINQ:
		lock_sock(sk);
		skb = skb_peek(&scp->other_receive_queue);
		if (skb) {
			amount = skb->len;
		} else {
			skb_queue_walk(&sk->sk_receive_queue, skb)
				amount += skb->len;
		}
		release_sock(sk);
		err = put_user(amount, (int __user *)arg);
		break;

	default:
		err = -ENOIOCTLCMD;
		break;
	}

	return err;
}
