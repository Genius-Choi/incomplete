static int pppol2tp_session_getsockopt(struct sock *sk,
				       struct l2tp_session *session,
				       int optname, int *val)
{
	int err = 0;

	switch (optname) {
	case PPPOL2TP_SO_RECVSEQ:
		*val = session->recv_seq;
		l2tp_info(session, PPPOL2TP_MSG_CONTROL,
			  "%s: get recv_seq=%d\n", session->name, *val);
		break;

	case PPPOL2TP_SO_SENDSEQ:
		*val = session->send_seq;
		l2tp_info(session, PPPOL2TP_MSG_CONTROL,
			  "%s: get send_seq=%d\n", session->name, *val);
		break;

	case PPPOL2TP_SO_LNSMODE:
		*val = session->lns_mode;
		l2tp_info(session, PPPOL2TP_MSG_CONTROL,
			  "%s: get lns_mode=%d\n", session->name, *val);
		break;

	case PPPOL2TP_SO_DEBUG:
		*val = session->debug;
		l2tp_info(session, PPPOL2TP_MSG_CONTROL, "%s: get debug=%d\n",
			  session->name, *val);
		break;

	case PPPOL2TP_SO_REORDERTO:
		*val = (int) jiffies_to_msecs(session->reorder_timeout);
		l2tp_info(session, PPPOL2TP_MSG_CONTROL,
			  "%s: get reorder_timeout=%d\n", session->name, *val);
		break;

	default:
		err = -ENOPROTOOPT;
	}

	return err;
}
