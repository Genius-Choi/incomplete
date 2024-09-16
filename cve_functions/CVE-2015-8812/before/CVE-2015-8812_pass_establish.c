static int pass_establish(struct t3cdev *tdev, struct sk_buff *skb, void *ctx)
{
	struct iwch_ep *ep = ctx;
	struct cpl_pass_establish *req = cplhdr(skb);

	PDBG("%s ep %p\n", __func__, ep);
	ep->snd_seq = ntohl(req->snd_isn);
	ep->rcv_seq = ntohl(req->rcv_isn);

	set_emss(ep, ntohs(req->tcp_opt));

	dst_confirm(ep->dst);
	state_set(&ep->com, MPA_REQ_WAIT);
	start_ep_timer(ep);

	return CPL_RET_BUF_DONE;
}
