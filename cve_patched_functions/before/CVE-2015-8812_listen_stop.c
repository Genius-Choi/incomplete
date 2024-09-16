static int listen_stop(struct iwch_listen_ep *ep)
{
	struct sk_buff *skb;
	struct cpl_close_listserv_req *req;

	PDBG("%s ep %p\n", __func__, ep);
	skb = get_skb(NULL, sizeof(*req), GFP_KERNEL);
	if (!skb) {
		printk(KERN_ERR MOD "%s - failed to alloc skb\n", __func__);
		return -ENOMEM;
	}
	req = (struct cpl_close_listserv_req *) skb_put(skb, sizeof(*req));
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	req->cpu_idx = 0;
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_CLOSE_LISTSRV_REQ, ep->stid));
	skb->priority = 1;
	return iwch_cxgb3_ofld_send(ep->com.tdev, skb);
}
