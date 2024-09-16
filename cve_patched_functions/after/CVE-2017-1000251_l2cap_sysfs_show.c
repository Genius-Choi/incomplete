static ssize_t l2cap_sysfs_show(struct class *dev, char *buf)
{
	struct sock *sk;
	struct hlist_node *node;
	char *str = buf;

	read_lock_bh(&l2cap_sk_list.lock);

	sk_for_each(sk, node, &l2cap_sk_list.head) {
		struct l2cap_pinfo *pi = l2cap_pi(sk);

		str += sprintf(str, "%s %s %d %d 0x%4.4x 0x%4.4x %d %d %d\n",
				batostr(&bt_sk(sk)->src), batostr(&bt_sk(sk)->dst),
				sk->sk_state, __le16_to_cpu(pi->psm), pi->scid,
				pi->dcid, pi->imtu, pi->omtu, pi->sec_level);
	}

	read_unlock_bh(&l2cap_sk_list.lock);

	return str - buf;
}
