static void dn_unhash_sock_bh(struct sock *sk)
{
	write_lock_bh(&dn_hash_lock);
	sk_del_node_init(sk);
	write_unlock_bh(&dn_hash_lock);
}
