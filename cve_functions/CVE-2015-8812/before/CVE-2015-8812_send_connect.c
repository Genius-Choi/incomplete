static int send_connect(struct iwch_ep *ep)
{
	struct cpl_act_open_req *req;
	struct sk_buff *skb;
	u32 opt0h, opt0l, opt2;
	unsigned int mtu_idx;
	int wscale;

	PDBG("%s ep %p\n", __func__, ep);

	skb = get_skb(NULL, sizeof(*req), GFP_KERNEL);
	if (!skb) {
		printk(KERN_ERR MOD "%s - failed to alloc skb.\n",
		       __func__);
		return -ENOMEM;
	}
	mtu_idx = find_best_mtu(T3C_DATA(ep->com.tdev), dst_mtu(ep->dst));
	wscale = compute_wscale(rcv_win);
	opt0h = V_NAGLE(0) |
	    V_NO_CONG(nocong) |
	    V_KEEP_ALIVE(1) |
	    F_TCAM_BYPASS |
	    V_WND_SCALE(wscale) |
	    V_MSS_IDX(mtu_idx) |
	    V_L2T_IDX(ep->l2t->idx) | V_TX_CHANNEL(ep->l2t->smt_idx);
	opt0l = V_TOS((ep->tos >> 2) & M_TOS) | V_RCV_BUFSIZ(rcv_win>>10);
	opt2 = F_RX_COALESCE_VALID | V_RX_COALESCE(0) | V_FLAVORS_VALID(1) |
	       V_CONG_CONTROL_FLAVOR(cong_flavor);
	skb->priority = CPL_PRIORITY_SETUP;
	set_arp_failure_handler(skb, act_open_req_arp_failure);

	req = (struct cpl_act_open_req *) skb_put(skb, sizeof(*req));
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_ACT_OPEN_REQ, ep->atid));
	req->local_port = ep->com.local_addr.sin_port;
	req->peer_port = ep->com.remote_addr.sin_port;
	req->local_ip = ep->com.local_addr.sin_addr.s_addr;
	req->peer_ip = ep->com.remote_addr.sin_addr.s_addr;
	req->opt0h = htonl(opt0h);
	req->opt0l = htonl(opt0l);
	req->params = 0;
	req->opt2 = htonl(opt2);
	return iwch_l2t_send(ep->com.tdev, skb, ep->l2t);
}
