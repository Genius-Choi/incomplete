static void stop_ep_timer(struct iwch_ep *ep)
{
	PDBG("%s ep %p\n", __func__, ep);
	if (!timer_pending(&ep->timer)) {
		WARN(1, "%s timer stopped when its not running!  ep %p state %u\n",
			__func__, ep, ep->com.state);
		return;
	}
	del_timer_sync(&ep->timer);
	put_ep(&ep->com);
}
