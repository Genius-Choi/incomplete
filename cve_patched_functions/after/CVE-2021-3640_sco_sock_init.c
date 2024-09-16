static void sco_sock_init(struct sock *sk, struct sock *parent)
{
	BT_DBG("sk %p", sk);

	if (parent) {
		sk->sk_type = parent->sk_type;
		bt_sk(sk)->flags = bt_sk(parent)->flags;
		security_sk_clone(parent, sk);
	} else {
		bt_sk(sk)->skb_put_cmsg = sco_skb_put_cmsg;
	}
}
