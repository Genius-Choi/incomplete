static int act_open_rpl(struct t3cdev *tdev, struct sk_buff *skb, void *ctx)
{
	struct iwch_ep *ep = ctx;
	struct cpl_act_open_rpl *rpl = cplhdr(skb);

	PDBG("%s ep %p status %u errno %d\n", __func__, ep, rpl->status,
	     status2errno(rpl->status));
	connect_reply_upcall(ep, status2errno(rpl->status));
	state_set(&ep->com, DEAD);
	if (ep->com.tdev->type != T3A && act_open_has_tid(rpl->status))
		release_tid(ep->com.tdev, GET_TID(rpl), NULL);
	cxgb3_free_atid(ep->com.tdev, ep->atid);
	dst_release(ep->dst);
	l2t_release(ep->com.tdev, ep->l2t);
	put_ep(&ep->com);
	return CPL_RET_BUF_DONE;
}
