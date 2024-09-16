static void llc_sap_mcast(struct llc_sap *sap,
			  const struct llc_addr *laddr,
			  struct sk_buff *skb)
{
	int i = 0, count = 256 / sizeof(struct sock *);
	struct sock *sk, *stack[count];
	struct llc_sock *llc;
	struct hlist_head *dev_hb = llc_sk_dev_hash(sap, skb->dev->ifindex);

	spin_lock_bh(&sap->sk_lock);
	hlist_for_each_entry(llc, dev_hb, dev_hash_node) {

		sk = &llc->sk;

		if (!llc_mcast_match(sap, laddr, skb, sk))
			continue;

		sock_hold(sk);
		if (i < count)
			stack[i++] = sk;
		else {
			llc_do_mcast(sap, skb, stack, i);
			i = 0;
		}
	}
	spin_unlock_bh(&sap->sk_lock);

	llc_do_mcast(sap, skb, stack, i);
}
