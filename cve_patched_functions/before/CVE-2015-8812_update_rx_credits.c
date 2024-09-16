static int update_rx_credits(struct iwch_ep *ep, u32 credits)
{
	struct cpl_rx_data_ack *req;
	struct sk_buff *skb;

	PDBG("%s ep %p credits %u\n", __func__, ep, credits);
	skb = get_skb(NULL, sizeof(*req), GFP_KERNEL);
	if (!skb) {
		printk(KERN_ERR MOD "update_rx_credits - cannot alloc skb!\n");
		return 0;
	}

	req = (struct cpl_rx_data_ack *) skb_put(skb, sizeof(*req));
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_RX_DATA_ACK, ep->hwtid));
	req->credit_dack = htonl(V_RX_CREDITS(credits) | V_RX_FORCE_ACK(1));
	skb->priority = CPL_PRIORITY_ACK;
	iwch_cxgb3_ofld_send(ep->com.tdev, skb);
	return credits;
}
