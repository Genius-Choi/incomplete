static void reject_cr(struct t3cdev *tdev, u32 hwtid, __be32 peer_ip,
		      struct sk_buff *skb)
{
	PDBG("%s t3cdev %p tid %u peer_ip %x\n", __func__, tdev, hwtid,
	     peer_ip);
	BUG_ON(skb_cloned(skb));
	skb_trim(skb, sizeof(struct cpl_tid_release));
	skb_get(skb);

	if (tdev->type != T3A)
		release_tid(tdev, hwtid, skb);
	else {
		struct cpl_pass_accept_rpl *rpl;

		rpl = cplhdr(skb);
		skb->priority = CPL_PRIORITY_SETUP;
		rpl->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
		OPCODE_TID(rpl) = htonl(MK_OPCODE_TID(CPL_PASS_ACCEPT_RPL,
						      hwtid));
		rpl->peer_ip = peer_ip;
		rpl->opt0h = htonl(F_TCAM_BYPASS);
		rpl->opt0l_status = htonl(CPL_PASS_OPEN_REJECT);
		rpl->opt2 = 0;
		rpl->rsvd = rpl->opt2;
		iwch_cxgb3_ofld_send(tdev, skb);
	}
}
