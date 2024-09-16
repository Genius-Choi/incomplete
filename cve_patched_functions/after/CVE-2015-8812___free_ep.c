void __free_ep(struct kref *kref)
{
	struct iwch_ep *ep;
	ep = container_of(container_of(kref, struct iwch_ep_common, kref),
			  struct iwch_ep, com);
	PDBG("%s ep %p state %s\n", __func__, ep, states[state_read(&ep->com)]);
	if (test_bit(RELEASE_RESOURCES, &ep->com.flags)) {
		cxgb3_remove_tid(ep->com.tdev, (void *)ep, ep->hwtid);
		dst_release(ep->dst);
		l2t_release(ep->com.tdev, ep->l2t);
	}
	kfree(ep);
}
