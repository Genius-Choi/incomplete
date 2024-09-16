static void dn_unhash_sock(struct sock *sk)
{
	write_lock(&dn_hash_lock);
	sk_del_node_init(sk);
	write_unlock(&dn_hash_lock);
}
