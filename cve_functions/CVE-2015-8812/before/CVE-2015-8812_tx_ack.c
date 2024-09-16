static int tx_ack(struct t3cdev *tdev, struct sk_buff *skb, void *ctx)
{
	struct iwch_ep *ep = ctx;
	struct cpl_wr_ack *hdr = cplhdr(skb);
	unsigned int credits = ntohs(hdr->credits);
	unsigned long flags;
	int post_zb = 0;

	PDBG("%s ep %p credits %u\n", __func__, ep, credits);

	if (credits == 0) {
		PDBG("%s 0 credit ack  ep %p state %u\n",
		     __func__, ep, state_read(&ep->com));
		return CPL_RET_BUF_DONE;
	}

	spin_lock_irqsave(&ep->com.lock, flags);
	BUG_ON(credits != 1);
	dst_confirm(ep->dst);
	if (!ep->mpa_skb) {
		PDBG("%s rdma_init wr_ack ep %p state %u\n",
			__func__, ep, ep->com.state);
		if (ep->mpa_attr.initiator) {
			PDBG("%s initiator ep %p state %u\n",
				__func__, ep, ep->com.state);
			if (peer2peer && ep->com.state == FPDU_MODE)
				post_zb = 1;
		} else {
			PDBG("%s responder ep %p state %u\n",
				__func__, ep, ep->com.state);
			if (ep->com.state == MPA_REQ_RCVD) {
				ep->com.rpl_done = 1;
				wake_up(&ep->com.waitq);
			}
		}
	} else {
		PDBG("%s lsm ack ep %p state %u freeing skb\n",
			__func__, ep, ep->com.state);
		kfree_skb(ep->mpa_skb);
		ep->mpa_skb = NULL;
	}
	spin_unlock_irqrestore(&ep->com.lock, flags);
	if (post_zb)
		iwch_post_zb_read(ep);
	return CPL_RET_BUF_DONE;
}
