int iwch_ep_redirect(void *ctx, struct dst_entry *old, struct dst_entry *new,
		     struct l2t_entry *l2t)
{
	struct iwch_ep *ep = ctx;

	if (ep->dst != old)
		return 0;

	PDBG("%s ep %p redirect to dst %p l2t %p\n", __func__, ep, new,
	     l2t);
	dst_hold(new);
	l2t_release(ep->com.tdev, ep->l2t);
	ep->l2t = l2t;
	dst_release(old);
	ep->dst = new;
	return 1;
}
