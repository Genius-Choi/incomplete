struct sock *ax25_make_new(struct sock *osk, struct ax25_dev *ax25_dev)
{
	struct sock *sk;
	ax25_cb *ax25, *oax25;

	sk = sk_alloc(sock_net(osk), PF_AX25, GFP_ATOMIC, osk->sk_prot, 0);
	if (sk == NULL)
		return NULL;

	if ((ax25 = ax25_create_cb()) == NULL) {
		sk_free(sk);
		return NULL;
	}

	switch (osk->sk_type) {
	case SOCK_DGRAM:
		break;
	case SOCK_SEQPACKET:
		break;
	default:
		sk_free(sk);
		ax25_cb_put(ax25);
		return NULL;
	}

	sock_init_data(NULL, sk);

	sk->sk_type     = osk->sk_type;
	sk->sk_priority = osk->sk_priority;
	sk->sk_protocol = osk->sk_protocol;
	sk->sk_rcvbuf   = osk->sk_rcvbuf;
	sk->sk_sndbuf   = osk->sk_sndbuf;
	sk->sk_state    = TCP_ESTABLISHED;
	sock_copy_flags(sk, osk);

	oax25 = sk_to_ax25(osk);

	ax25->modulus = oax25->modulus;
	ax25->backoff = oax25->backoff;
	ax25->pidincl = oax25->pidincl;
	ax25->iamdigi = oax25->iamdigi;
	ax25->rtt     = oax25->rtt;
	ax25->t1      = oax25->t1;
	ax25->t2      = oax25->t2;
	ax25->t3      = oax25->t3;
	ax25->n2      = oax25->n2;
	ax25->idle    = oax25->idle;
	ax25->paclen  = oax25->paclen;
	ax25->window  = oax25->window;

	ax25->ax25_dev    = ax25_dev;
	ax25->source_addr = oax25->source_addr;

	if (oax25->digipeat != NULL) {
		ax25->digipeat = kmemdup(oax25->digipeat, sizeof(ax25_digi),
					 GFP_ATOMIC);
		if (ax25->digipeat == NULL) {
			sk_free(sk);
			ax25_cb_put(ax25);
			return NULL;
		}
	}

	ax25_sk(sk)->cb = ax25;
	sk->sk_destruct = ax25_free_sock;
	ax25->sk    = sk;

	return sk;
}
