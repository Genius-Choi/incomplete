static int terminate(struct t3cdev *tdev, struct sk_buff *skb, void *ctx)
{
	struct iwch_ep *ep = ctx;

	if (state_read(&ep->com) != FPDU_MODE)
		return CPL_RET_BUF_DONE;

	PDBG("%s ep %p\n", __func__, ep);
	skb_pull(skb, sizeof(struct cpl_rdma_terminate));
	PDBG("%s saving %d bytes of term msg\n", __func__, skb->len);
	skb_copy_from_linear_data(skb, ep->com.qp->attr.terminate_buffer,
				  skb->len);
	ep->com.qp->attr.terminate_msg_len = skb->len;
	ep->com.qp->attr.is_terminate_local = 0;
	return CPL_RET_BUF_DONE;
}
