static unsigned int macvtap_poll(struct file *file, poll_table * wait)
{
	struct macvtap_queue *q = file->private_data;
	unsigned int mask = POLLERR;

	if (!q)
		goto out;

	mask = 0;
	poll_wait(file, &q->wq.wait, wait);

	if (!skb_queue_empty(&q->sk.sk_receive_queue))
		mask |= POLLIN | POLLRDNORM;

	if (sock_writeable(&q->sk) ||
	    (!test_and_set_bit(SOCK_ASYNC_NOSPACE, &q->sock.flags) &&
	     sock_writeable(&q->sk)))
		mask |= POLLOUT | POLLWRNORM;

out:
	return mask;
}
