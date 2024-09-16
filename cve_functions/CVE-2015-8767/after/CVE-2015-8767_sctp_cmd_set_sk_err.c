static void sctp_cmd_set_sk_err(struct sctp_association *asoc, int error)
{
	struct sock *sk = asoc->base.sk;

	if (!sctp_style(sk, UDP))
		sk->sk_err = error;
}
