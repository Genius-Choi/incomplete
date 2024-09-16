static inline int ib_ucm_new_cm_id(int event)
{
	return event == IB_CM_REQ_RECEIVED || event == IB_CM_SIDR_REQ_RECEIVED;
}
