struct sock *dn_find_by_skb(struct sk_buff *skb)
{
	struct dn_skb_cb *cb = DN_SKB_CB(skb);
	struct sock *sk;
	struct dn_scp *scp;

	read_lock(&dn_hash_lock);
	sk_for_each(sk, &dn_sk_hash[le16_to_cpu(cb->dst_port) & DN_SK_HASH_MASK]) {
		scp = DN_SK(sk);
		if (cb->src != dn_saddr2dn(&scp->peer))
			continue;
		if (cb->dst_port != scp->addrloc)
			continue;
		if (scp->addrrem && (cb->src_port != scp->addrrem))
			continue;
		sock_hold(sk);
		goto found;
	}
	sk = NULL;
found:
	read_unlock(&dn_hash_lock);
	return sk;
}
