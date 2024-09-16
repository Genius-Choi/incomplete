static int send_halfclose(struct iwch_ep *ep, gfp_t gfp)
{
	struct cpl_close_con_req *req;
	struct sk_buff *skb;

	PDBG("%s ep %p\n", __func__, ep);
	skb = get_skb(NULL, sizeof(*req), gfp);
	if (!skb) {
		printk(KERN_ERR MOD "%s - failed to alloc skb\n", __func__);
		return -ENOMEM;
	}
	skb->priority = CPL_PRIORITY_DATA;
	set_arp_failure_handler(skb, arp_failure_discard);
	req = (struct cpl_close_con_req *) skb_put(skb, sizeof(*req));
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_OFLD_CLOSE_CON));
	req->wr.wr_lo = htonl(V_WR_TID(ep->hwtid));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_CLOSE_CON_REQ, ep->hwtid));
	return iwch_l2t_send(ep->com.tdev, skb, ep->l2t);
}
