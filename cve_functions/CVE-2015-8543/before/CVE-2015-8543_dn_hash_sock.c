static int dn_hash_sock(struct sock *sk)
{
	struct dn_scp *scp = DN_SK(sk);
	struct hlist_head *list;
	int rv = -EUSERS;

	BUG_ON(sk_hashed(sk));

	write_lock_bh(&dn_hash_lock);

	if (!scp->addrloc && !port_alloc(sk))
		goto out;

	rv = -EADDRINUSE;
	if ((list = dn_find_list(sk)) == NULL)
		goto out;

	sk_add_node(sk, list);
	rv = 0;
out:
	write_unlock_bh(&dn_hash_lock);
	return rv;
}
