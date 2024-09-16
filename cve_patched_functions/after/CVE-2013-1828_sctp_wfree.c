static void sctp_wfree(struct sk_buff *skb)
{
	struct sctp_association *asoc;
	struct sctp_chunk *chunk;
	struct sock *sk;

	/* Get the saved chunk pointer.  */
	chunk = *((struct sctp_chunk **)(skb->cb));
	asoc = chunk->asoc;
	sk = asoc->base.sk;
	asoc->sndbuf_used -= SCTP_DATA_SNDSIZE(chunk) +
				sizeof(struct sk_buff) +
				sizeof(struct sctp_chunk);

	atomic_sub(sizeof(struct sctp_chunk), &sk->sk_wmem_alloc);

	/*
	 * This undoes what is done via sctp_set_owner_w and sk_mem_charge
	 */
	sk->sk_wmem_queued   -= skb->truesize;
	sk_mem_uncharge(sk, skb->truesize);

	sock_wfree(skb);
	__sctp_write_space(asoc);

	sctp_association_put(asoc);
}
