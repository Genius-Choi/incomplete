static int close_listsrv_rpl(struct t3cdev *tdev, struct sk_buff *skb,
			     void *ctx)
{
	struct iwch_listen_ep *ep = ctx;
	struct cpl_close_listserv_rpl *rpl = cplhdr(skb);

	PDBG("%s ep %p\n", __func__, ep);
	ep->com.rpl_err = status2errno(rpl->status);
	ep->com.rpl_done = 1;
	wake_up(&ep->com.waitq);
	return CPL_RET_BUF_DONE;
}
