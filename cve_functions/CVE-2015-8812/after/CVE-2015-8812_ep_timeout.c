static void ep_timeout(unsigned long arg)
{
	struct iwch_ep *ep = (struct iwch_ep *)arg;
	struct iwch_qp_attributes attrs;
	unsigned long flags;
	int abort = 1;

	spin_lock_irqsave(&ep->com.lock, flags);
	PDBG("%s ep %p tid %u state %d\n", __func__, ep, ep->hwtid,
	     ep->com.state);
	switch (ep->com.state) {
	case MPA_REQ_SENT:
		__state_set(&ep->com, ABORTING);
		connect_reply_upcall(ep, -ETIMEDOUT);
		break;
	case MPA_REQ_WAIT:
		__state_set(&ep->com, ABORTING);
		break;
	case CLOSING:
	case MORIBUND:
		if (ep->com.cm_id && ep->com.qp) {
			attrs.next_state = IWCH_QP_STATE_ERROR;
			iwch_modify_qp(ep->com.qp->rhp,
				     ep->com.qp, IWCH_QP_ATTR_NEXT_STATE,
				     &attrs, 1);
		}
		__state_set(&ep->com, ABORTING);
		break;
	default:
		WARN(1, "%s unexpected state ep %p state %u\n",
			__func__, ep, ep->com.state);
		abort = 0;
	}
	spin_unlock_irqrestore(&ep->com.lock, flags);
	if (abort)
		abort_connection(ep, NULL, GFP_ATOMIC);
	put_ep(&ep->com);
}
