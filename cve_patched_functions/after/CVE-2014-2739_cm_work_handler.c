static void cm_work_handler(struct work_struct *_work)
{
	struct cm_work *work = container_of(_work, struct cm_work, work.work);
	int ret;

	switch (work->cm_event.event) {
	case IB_CM_REQ_RECEIVED:
		ret = cm_req_handler(work);
		break;
	case IB_CM_MRA_RECEIVED:
		ret = cm_mra_handler(work);
		break;
	case IB_CM_REJ_RECEIVED:
		ret = cm_rej_handler(work);
		break;
	case IB_CM_REP_RECEIVED:
		ret = cm_rep_handler(work);
		break;
	case IB_CM_RTU_RECEIVED:
		ret = cm_rtu_handler(work);
		break;
	case IB_CM_USER_ESTABLISHED:
		ret = cm_establish_handler(work);
		break;
	case IB_CM_DREQ_RECEIVED:
		ret = cm_dreq_handler(work);
		break;
	case IB_CM_DREP_RECEIVED:
		ret = cm_drep_handler(work);
		break;
	case IB_CM_SIDR_REQ_RECEIVED:
		ret = cm_sidr_req_handler(work);
		break;
	case IB_CM_SIDR_REP_RECEIVED:
		ret = cm_sidr_rep_handler(work);
		break;
	case IB_CM_LAP_RECEIVED:
		ret = cm_lap_handler(work);
		break;
	case IB_CM_APR_RECEIVED:
		ret = cm_apr_handler(work);
		break;
	case IB_CM_TIMEWAIT_EXIT:
		ret = cm_timewait_handler(work);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	if (ret)
		cm_free_work(work);
}
