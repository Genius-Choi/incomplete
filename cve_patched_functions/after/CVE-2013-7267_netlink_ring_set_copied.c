static void netlink_ring_set_copied(struct sock *sk, struct sk_buff *skb)
{
	struct netlink_sock *nlk = nlk_sk(sk);
	struct netlink_ring *ring = &nlk->rx_ring;
	struct nl_mmap_hdr *hdr;

	spin_lock_bh(&sk->sk_receive_queue.lock);
	hdr = netlink_current_frame(ring, NL_MMAP_STATUS_UNUSED);
	if (hdr == NULL) {
		spin_unlock_bh(&sk->sk_receive_queue.lock);
		kfree_skb(skb);
		netlink_overrun(sk);
		return;
	}
	netlink_increment_head(ring);
	__skb_queue_tail(&sk->sk_receive_queue, skb);
	spin_unlock_bh(&sk->sk_receive_queue.lock);

	hdr->nm_len	= skb->len;
	hdr->nm_group	= NETLINK_CB(skb).dst_group;
	hdr->nm_pid	= NETLINK_CB(skb).creds.pid;
	hdr->nm_uid	= from_kuid(sk_user_ns(sk), NETLINK_CB(skb).creds.uid);
	hdr->nm_gid	= from_kgid(sk_user_ns(sk), NETLINK_CB(skb).creds.gid);
	netlink_set_status(hdr, NL_MMAP_STATUS_COPY);
}
