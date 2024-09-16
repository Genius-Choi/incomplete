static void llc_conn_send_pdus(struct sock *sk)
{
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&sk->sk_write_queue)) != NULL) {
		struct llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

		if (LLC_PDU_TYPE_IS_I(pdu) &&
		    !(skb->dev->flags & IFF_LOOPBACK)) {
			struct sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);

			skb_queue_tail(&llc_sk(sk)->pdu_unack_q, skb);
			if (!skb2)
				break;
			skb = skb2;
		}
		dev_queue_xmit(skb);
	}
}
