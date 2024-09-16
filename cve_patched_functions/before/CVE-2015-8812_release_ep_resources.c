static void release_ep_resources(struct iwch_ep *ep)
{
	PDBG("%s ep %p tid %d\n", __func__, ep, ep->hwtid);
	set_bit(RELEASE_RESOURCES, &ep->com.flags);
	put_ep(&ep->com);
}
