int iwch_resume_tid(struct iwch_ep *ep)
{
	struct cpl_set_tcb_field *req;
	struct sk_buff *skb = get_skb(NULL, sizeof(*req), GFP_KERNEL);

	if (!skb)
		return -ENOMEM;
	req = (struct cpl_set_tcb_field *) skb_put(skb, sizeof(*req));
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	req->wr.wr_lo = htonl(V_WR_TID(ep->hwtid));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_SET_TCB_FIELD, ep->hwtid));
	req->reply = 0;
	req->cpu_idx = 0;
	req->word = htons(W_TCB_RX_QUIESCE);
	req->mask = cpu_to_be64(1ULL << S_TCB_RX_QUIESCE);
	req->val = 0;

	skb->priority = CPL_PRIORITY_DATA;
	return iwch_cxgb3_ofld_send(ep->com.tdev, skb);
}
