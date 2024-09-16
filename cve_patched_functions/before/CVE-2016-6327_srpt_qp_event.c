static void srpt_qp_event(struct ib_event *event, struct srpt_rdma_ch *ch)
{
	pr_debug("QP event %d on cm_id=%p sess_name=%s state=%d\n",
		 event->event, ch->cm_id, ch->sess_name, srpt_get_ch_state(ch));

	switch (event->event) {
	case IB_EVENT_COMM_EST:
		ib_cm_notify(ch->cm_id, event->event);
		break;
	case IB_EVENT_QP_LAST_WQE_REACHED:
		if (srpt_test_and_set_ch_state(ch, CH_DRAINING,
					       CH_RELEASING))
			srpt_release_channel(ch);
		else
			pr_debug("%s: state %d - ignored LAST_WQE.\n",
				 ch->sess_name, srpt_get_ch_state(ch));
		break;
	default:
		pr_err("received unrecognized IB QP event %d\n", event->event);
		break;
	}
}
