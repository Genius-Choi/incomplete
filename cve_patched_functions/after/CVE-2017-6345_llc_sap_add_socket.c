void llc_sap_add_socket(struct llc_sap *sap, struct sock *sk)
{
	struct llc_sock *llc = llc_sk(sk);
	struct hlist_head *dev_hb = llc_sk_dev_hash(sap, llc->dev->ifindex);
	struct hlist_nulls_head *laddr_hb = llc_sk_laddr_hash(sap, &llc->laddr);

	llc_sap_hold(sap);
	llc_sk(sk)->sap = sap;

	spin_lock_bh(&sap->sk_lock);
	sap->sk_count++;
	sk_nulls_add_node_rcu(sk, laddr_hb);
	hlist_add_head(&llc->dev_hash_node, dev_hb);
	spin_unlock_bh(&sap->sk_lock);
}
