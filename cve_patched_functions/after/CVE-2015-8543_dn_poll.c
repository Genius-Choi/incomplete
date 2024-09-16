static unsigned int dn_poll(struct file *file, struct socket *sock, poll_table  *wait)
{
	struct sock *sk = sock->sk;
	struct dn_scp *scp = DN_SK(sk);
	int mask = datagram_poll(file, sock, wait);

	if (!skb_queue_empty(&scp->other_receive_queue))
		mask |= POLLRDBAND;

	return mask;
}
