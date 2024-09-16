static struct hlist_head *dn_find_list(struct sock *sk)
{
	struct dn_scp *scp = DN_SK(sk);

	if (scp->addr.sdn_flags & SDF_WILD)
		return hlist_empty(&dn_wild_sk) ? &dn_wild_sk : NULL;

	return &dn_sk_hash[le16_to_cpu(scp->addrloc) & DN_SK_HASH_MASK];
}
