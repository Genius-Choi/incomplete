static void unix_set_peek_off(struct sock *sk, int val)
{
	struct unix_sock *u = unix_sk(sk);

	mutex_lock(&u->readlock);
	sk->sk_peek_off = val;
	mutex_unlock(&u->readlock);
}
