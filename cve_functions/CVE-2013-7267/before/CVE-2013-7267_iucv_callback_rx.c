static void iucv_callback_rx(struct iucv_path *path, struct iucv_message *msg)
{
	struct sock *sk = path->private;
	struct iucv_sock *iucv = iucv_sk(sk);
	struct sk_buff *skb;
	struct sock_msg_q *save_msg;
	int len;

	if (sk->sk_shutdown & RCV_SHUTDOWN) {
		pr_iucv->message_reject(path, msg);
		return;
	}

	spin_lock(&iucv->message_q.lock);

	if (!list_empty(&iucv->message_q.list) ||
	    !skb_queue_empty(&iucv->backlog_skb_q))
		goto save_message;

	len = atomic_read(&sk->sk_rmem_alloc);
	len += SKB_TRUESIZE(iucv_msg_length(msg));
	if (len > sk->sk_rcvbuf)
		goto save_message;

	skb = alloc_skb(iucv_msg_length(msg), GFP_ATOMIC | GFP_DMA);
	if (!skb)
		goto save_message;

	iucv_process_message(sk, skb, path, msg);
	goto out_unlock;

save_message:
	save_msg = kzalloc(sizeof(struct sock_msg_q), GFP_ATOMIC | GFP_DMA);
	if (!save_msg)
		goto out_unlock;
	save_msg->path = path;
	save_msg->msg = *msg;

	list_add_tail(&save_msg->list, &iucv->message_q.list);

out_unlock:
	spin_unlock(&iucv->message_q.lock);
}
