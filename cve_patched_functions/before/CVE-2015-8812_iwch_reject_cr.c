int iwch_reject_cr(struct iw_cm_id *cm_id, const void *pdata, u8 pdata_len)
{
	int err;
	struct iwch_ep *ep = to_ep(cm_id);
	PDBG("%s ep %p tid %u\n", __func__, ep, ep->hwtid);

	if (state_read(&ep->com) == DEAD) {
		put_ep(&ep->com);
		return -ECONNRESET;
	}
	BUG_ON(state_read(&ep->com) != MPA_REQ_RCVD);
	if (mpa_rev == 0)
		abort_connection(ep, NULL, GFP_KERNEL);
	else {
		err = send_mpa_reject(ep, pdata, pdata_len);
		err = iwch_ep_disconnect(ep, 0, GFP_KERNEL);
	}
	put_ep(&ep->com);
	return 0;
}
