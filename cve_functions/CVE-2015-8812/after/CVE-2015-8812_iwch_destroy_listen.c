int iwch_destroy_listen(struct iw_cm_id *cm_id)
{
	int err;
	struct iwch_listen_ep *ep = to_listen_ep(cm_id);

	PDBG("%s ep %p\n", __func__, ep);

	might_sleep();
	state_set(&ep->com, DEAD);
	ep->com.rpl_done = 0;
	ep->com.rpl_err = 0;
	err = listen_stop(ep);
	if (err)
		goto done;
	wait_event(ep->com.waitq, ep->com.rpl_done);
	cxgb3_free_stid(ep->com.tdev, ep->stid);
done:
	err = ep->com.rpl_err;
	cm_id->rem_ref(cm_id);
	put_ep(&ep->com);
	return err;
}
