static int send_abort(struct iwch_ep *ep, struct sk_buff *skb, gfp_t gfp)
{
	struct cpl_abort_req *req;

	PDBG("%s ep %p\n", __func__, ep);
	skb = get_skb(skb, sizeof(*req), gfp);
	if (!skb) {
		printk(KERN_ERR MOD "%s - failed to alloc skb.\n",
		       __func__);
		return -ENOMEM;
	}
	skb->priority = CPL_PRIORITY_DATA;
	set_arp_failure_handler(skb, abort_arp_failure);
	req = (struct cpl_abort_req *) skb_put(skb, sizeof(*req));
	memset(req, 0, sizeof(*req));
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_OFLD_HOST_ABORT_CON_REQ));
	req->wr.wr_lo = htonl(V_WR_TID(ep->hwtid));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_ABORT_REQ, ep->hwtid));
	req->cmd = CPL_ABORT_SEND_RST;
	return iwch_l2t_send(ep->com.tdev, skb, ep->l2t);
}
