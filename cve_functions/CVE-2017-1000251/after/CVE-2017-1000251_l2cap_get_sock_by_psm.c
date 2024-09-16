static inline struct sock *l2cap_get_sock_by_psm(int state, __le16 psm, bdaddr_t *src)
{
	struct sock *s;
	read_lock(&l2cap_sk_list.lock);
	s = __l2cap_get_sock_by_psm(state, psm, src);
	if (s)
		bh_lock_sock(s);
	read_unlock(&l2cap_sk_list.lock);
	return s;
}
