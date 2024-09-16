static int ec_status(struct t3cdev *tdev, struct sk_buff *skb, void *ctx)
{
	struct cpl_rdma_ec_status *rep = cplhdr(skb);
	struct iwch_ep *ep = ctx;

	PDBG("%s ep %p tid %u status %d\n", __func__, ep, ep->hwtid,
	     rep->status);
	if (rep->status) {
		struct iwch_qp_attributes attrs;

		printk(KERN_ERR MOD "%s BAD CLOSE - Aborting tid %u\n",
		       __func__, ep->hwtid);
		stop_ep_timer(ep);
		attrs.next_state = IWCH_QP_STATE_ERROR;
		iwch_modify_qp(ep->com.qp->rhp,
			       ep->com.qp, IWCH_QP_ATTR_NEXT_STATE,
			       &attrs, 1);
		abort_connection(ep, NULL, GFP_KERNEL);
	}
	return CPL_RET_BUF_DONE;
}
