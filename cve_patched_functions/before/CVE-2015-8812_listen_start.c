static int listen_start(struct iwch_listen_ep *ep)
{
	struct sk_buff *skb;
	struct cpl_pass_open_req *req;

	PDBG("%s ep %p\n", __func__, ep);
	skb = get_skb(NULL, sizeof(*req), GFP_KERNEL);
	if (!skb) {
		printk(KERN_ERR MOD "t3c_listen_start failed to alloc skb!\n");
		return -ENOMEM;
	}

	req = (struct cpl_pass_open_req *) skb_put(skb, sizeof(*req));
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_PASS_OPEN_REQ, ep->stid));
	req->local_port = ep->com.local_addr.sin_port;
	req->local_ip = ep->com.local_addr.sin_addr.s_addr;
	req->peer_port = 0;
	req->peer_ip = 0;
	req->peer_netmask = 0;
	req->opt0h = htonl(F_DELACK | F_TCAM_BYPASS);
	req->opt0l = htonl(V_RCV_BUFSIZ(rcv_win>>10));
	req->opt1 = htonl(V_CONN_POLICY(CPL_CONN_POLICY_ASK));

	skb->priority = 1;
	return iwch_cxgb3_ofld_send(ep->com.tdev, skb);
}
