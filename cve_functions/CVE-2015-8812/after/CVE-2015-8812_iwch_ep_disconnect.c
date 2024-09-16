int iwch_ep_disconnect(struct iwch_ep *ep, int abrupt, gfp_t gfp)
{
	int ret=0;
	unsigned long flags;
	int close = 0;
	int fatal = 0;
	struct t3cdev *tdev;
	struct cxio_rdev *rdev;

	spin_lock_irqsave(&ep->com.lock, flags);

	PDBG("%s ep %p state %s, abrupt %d\n", __func__, ep,
	     states[ep->com.state], abrupt);

	tdev = (struct t3cdev *)ep->com.tdev;
	rdev = (struct cxio_rdev *)tdev->ulp;
	if (cxio_fatal_error(rdev)) {
		fatal = 1;
		close_complete_upcall(ep);
		ep->com.state = DEAD;
	}
	switch (ep->com.state) {
	case MPA_REQ_WAIT:
	case MPA_REQ_SENT:
	case MPA_REQ_RCVD:
	case MPA_REP_SENT:
	case FPDU_MODE:
		close = 1;
		if (abrupt)
			ep->com.state = ABORTING;
		else {
			ep->com.state = CLOSING;
			start_ep_timer(ep);
		}
		set_bit(CLOSE_SENT, &ep->com.flags);
		break;
	case CLOSING:
		if (!test_and_set_bit(CLOSE_SENT, &ep->com.flags)) {
			close = 1;
			if (abrupt) {
				stop_ep_timer(ep);
				ep->com.state = ABORTING;
			} else
				ep->com.state = MORIBUND;
		}
		break;
	case MORIBUND:
	case ABORTING:
	case DEAD:
		PDBG("%s ignoring disconnect ep %p state %u\n",
		     __func__, ep, ep->com.state);
		break;
	default:
		BUG();
		break;
	}

	spin_unlock_irqrestore(&ep->com.lock, flags);
	if (close) {
		if (abrupt)
			ret = send_abort(ep, NULL, gfp);
		else
			ret = send_halfclose(ep, gfp);
		if (ret)
			fatal = 1;
	}
	if (fatal)
		release_ep_resources(ep);
	return ret;
}
